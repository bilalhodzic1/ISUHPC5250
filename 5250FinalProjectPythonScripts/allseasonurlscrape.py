import requests
from bs4 import BeautifulSoup
import re
import json
import time
import string


letters = [letter for letter in string.ascii_lowercase if letter != 'x']
all_game_stat_urls = []
for letter in letters:
    URL = f"https://www.basketball-reference.com/players/{letter}/"
    page = requests.get(URL)
    soup = BeautifulSoup(page.content, "html.parser")
    time.sleep(4)
    player_tds = soup.find_all(attrs={"data-stat":"player"})
    player_tds.pop(0)
    url_endings = []
    for td in player_tds:
        anchor = td.find("a")
        url_endings.append(anchor.get("href"))
    for player_ending in url_endings:
        PLAYER_URL = f"https://www.basketball-reference.com/{player_ending}"
        player_page = requests.get(PLAYER_URL)
        player_soup = BeautifulSoup(player_page.content, "html.parser")
        player_season_url_endings = []
        for li in player_soup.find_all('li'):
            first_tag = next((child for child in li.children if child.name), None)
            if first_tag and first_tag.name == 'span' and first_tag.get_text(strip=True) == 'Game Logs':
                inner_tags = li.find_all('li')
                pattern = re.compile(r'^\d{4}-\d{2}$')
                for tag in inner_tags:
                    game_season_anchor = tag.find('a')
                    if(pattern.match(game_season_anchor.text)):
                        player_season_url_endings.append(game_season_anchor.get("href"))
        prefix = 'https://www.basketball-reference.com'
        player_season_urls = [prefix + item for item in player_season_url_endings]
        all_game_stat_urls = all_game_stat_urls + player_season_urls
        time.sleep(4)
with open('allgameurls.json', 'w') as f:
    json.dump(all_game_stat_urls, f)
