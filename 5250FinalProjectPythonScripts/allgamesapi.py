import time
import pandas as pd
from tqdm import tqdm
from nba_api.stats.static import players
from nba_api.stats.endpoints import playergamelog, commonplayerinfo
import warnings
import requests

# Suppress FutureWarning (for pandas concat stuff)
warnings.simplefilter(action='ignore', category=FutureWarning)

# Get all NBA players
all_players = players.get_players()
print(f"Found {len(all_players)} players.")

# Prepare master DataFrame
master_df = pd.DataFrame()
failures = []  # <--- NEW: List to track any failed pulls

# Progress bar
for player in tqdm(all_players, desc="Players Progress", unit="player"):
    player_id = player['id']
    player_name = player['full_name']
    
    try:
        # Get FROM_YEAR and TO_YEAR
        info = commonplayerinfo.CommonPlayerInfo(player_id=player_id)
        data = info.get_data_frames()[0]
        from_year = int(data['FROM_YEAR'].values[0])
        to_year = int(data['TO_YEAR'].values[0])
        
        for year in range(from_year, to_year + 1):
            season_start = str(year)
            season_end = str((year + 1) % 100).zfill(2)
            season = f"{season_start}-{season_end}"
            
            try:
                # Pull game logs for this season
                gamelog = playergamelog.PlayerGameLog(
                    player_id=player_id,
                    season=season,
                    season_type_all_star='Regular Season'
                )
                df = gamelog.get_data_frames()[0]
                
                if not df.empty:
                    df['PLAYER_NAME'] = player_name
                    df['SEASON'] = season
                    master_df = pd.concat([master_df, df], ignore_index=True)
                    
                time.sleep(0.7)  # Be nice to the API
                
            except (requests.exceptions.RequestException, Exception) as e:
                print(f"  ❌ Error pulling {player_name} {season}: {e}")
                failures.append({'player': player_name, 'season': season, 'error': str(e)})
                time.sleep(1)  # Cool down after error

    except (requests.exceptions.RequestException, Exception) as e:
        print(f"❌ Error getting info for {player_name}: {e}")
        failures.append({'player': player_name, 'season': 'N/A', 'error': str(e)})
        time.sleep(1)

# Save results
master_df.to_csv('nba_player_game_logs_alltime.csv', index=False)
print("✅ Game logs saved!")

# Save failures
if failures:
    failures_df = pd.DataFrame(failures)
    failures_df.to_csv('nba_failures.csv', index=False)