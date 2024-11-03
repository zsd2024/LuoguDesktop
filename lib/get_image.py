import requests


def get_background_url() -> str:
    url = "https://cn.bing.com/HPImageArchive.aspx?format=js&n=1"
    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36"
    }
    response = requests.get(url, headers=headers)
    if response.status_code == 200:
        data = response.json()
        url = "https://cn.bing.com" + data["images"][0]["url"]
        return url
    else:
        return None
