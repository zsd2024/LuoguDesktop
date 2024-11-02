import re
import requests
import json
import urllib.parse
import ddddocr  # type: ignore
from typing import Optional, Tuple, Dict, Any

user_headers: dict[str, str] = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"
}

cookies: dict[str, str] = {"_uid": "0"}
ocr: ddddocr.DdddOcr = ddddocr.DdddOcr()


def fetch_user_data(uid: str) -> Tuple[Optional[str], Optional[str]]:
    url: str = f"https://www.luogu.com.cn/user/{uid}"
    try:
        response: requests.Response = requests.get(
            url, headers=user_headers, cookies=cookies
        )
        response.raise_for_status()  # Raise an exception for HTTP errors

        html_content: str = response.text
        start: int = html_content.find(
            'window._feInjection = JSON.parse(decodeURIComponent("'
        ) + len('window._feInjection = JSON.parse(decodeURIComponent("')
        end: int = html_content.find('"));', start)

        if start != -1 and end != -1:
            encoded_data: str = html_content[start:end]
            json_data: Dict[str, Any] = json.loads(urllib.parse.unquote(encoded_data))

            # 明确获取用户数据的类型
            user_data: Optional[Dict[str, Any]] = json_data.get("currentData", {}).get(
                "user"
            )
            if user_data:
                username: Optional[str] = user_data.get("name")
                avatar_url: Optional[str] = user_data.get("avatar")
                return username, avatar_url

    except requests.RequestException as e:
        print(f"请求失败: {e}")
    return None, None


def login(username: str, password: str) -> Dict[str, str]:
    session: requests.Session = requests.Session()
    session.get(
        url="https://www.luogu.com.cn",
        headers={"User-Agent": user_headers["User-Agent"]},
    )

    captcha_response: requests.Response = session.get(
        url="https://www.luogu.com.cn/lg4/captcha",
        headers={"User-Agent": user_headers["User-Agent"]},
    )
    if captcha_response.status_code != 200:
        raise ValueError("获取验证码失败")

    captcha: str = process_captcha(captcha_response.content)

    response: requests.Response = session.post(
        url="https://www.luogu.com.cn/do-auth/password",
        headers={"User-Agent": user_headers["User-Agent"]},
        json={
            "captcha": captcha,
            "username": username,
            "password": password,
        },
    )

    if response.status_code == 200:
        return dict(session.cookies)
    else:
        raise ValueError(json.loads(response.text)["errorMessage"])


def process_captcha(captcha: bytes) -> str:
    return ocr.classification(img=captcha)  # type: ignore
