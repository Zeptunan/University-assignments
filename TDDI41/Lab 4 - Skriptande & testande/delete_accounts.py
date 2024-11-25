import subprocess

# Lista över användare att ta bort
users = [
    "cítàrt515", 'dw"tle342', "tho'ca394", "tho'jf634", "kamavy695",
    "valihp958", "valirl256", "malitx543", "masr429", "öösg520",
    "mälilixy561", "бониvq962", "慈禧cc366", "svpeea773"
]
for user in users:
    try:
        subprocess.run(['userdel', '-r', user], check=True)
        print(f"Användare {user} har raderats.")
    except subprocess.CalledProcessError as e:
        print(f"Misslyckades med att radera användare {user}: {e}")



















# def användarnamn_existenter(användarnamn):
    # Kontrollera om användarnamnet redan finns i systemet
  #  with open("/etc/passwd", "r") as file:
   #     system_users = [line.split(':')[0] for line in file.readlines()]
   # return användarnamn in system_users
