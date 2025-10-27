#!/usr/bin/env python3
import subprocess
x=0
titles = []

repo = "chandra-ont/Tres_Liberi_Divortii"
titlr = input("list")

titles = [t.strip() for t in titlr.split(",") if t.strip()]

for title in titles:
    if title:
        print(f"Creating issue: {title}")
        subprocess.run(["gh", "issue", "create","--repo",repo ,"--title", title, "--body", "add somme thing here", "-l", "enhancement"])

print("Done.")
