import time
from datetime import datetime as dt

hosts = r"/etc/hosts"
redirect = r"127.0.0.1"
websites = ["www.facebook.com", "facebook.com", "www.twitter.com", "twitter.com", "www.fanfou.com", "fanfou.com", "www.feedly.com", "feedly.com"]

while True:
    if dt(dt.now().year, dt.now().month, dt.now().day, 8) < dt.now() < dt(dt.now().year, dt.now().month, dt.now().day, 17):
        print("No slacking off now. ")
        with open(hosts, "r+") as file:
            content = file.read()
            for website in websites:
                if website not in content:
                    file.write(redirect + " " + website + "\n")
    else: 
        print("Fun time!")
        with open(hosts, "r+") as file:
            content = file.readlines()
            file.seek(0)
            for line in content:
                if not any(website in line for website in websites):
                    file.write(line)
            file.truncate()
    time.sleep(30)