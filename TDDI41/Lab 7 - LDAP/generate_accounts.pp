from unidecode import unidecode
import subprocess
import random
import string
import sys

def main():
    if len(sys.argv) != 2:
        print("Användning: python3 ./generate_accounts.py <filnamn>")
        sys.exit(1)

    filnamn = sys.argv[1]
    with open(filnamn, 'r') as f:
        namn_list = [namn.strip() for namn in f if namn.strip()]

    for namn in namn_list:
        användarnamn = generera_användarnamn(namn)
        lösenord = generera_lösenord()
        uid = generera_uid()

        skapa_användarkonto(användarnamn, lösenord, uid)

    print("Alla användarkonton har skapats.")

def generera_användarnamn(namn):
    namn = unidecode(namn)
    initialer = ''.join([del_namn[:2] for del_namn in namn.lower().split()[:2] if del_namn[:2].isalnum()])
    slumpade_bokstäver = ''.join(random.choices(string.ascii_lowercase, k=2))
    nummer = random.randint(100, 999)
    användarnamn = f"{initialer}{slumpade_bokstäver}{nummer}"

    print(f"Ditt användarnamn är: {användarnamn}")
    return användarnamn

def generera_lösenord():
    length = random.randint(5, 7)
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def generera_uid():
    result = subprocess.run(["getent", "passwd"], capture_output=True, text=True)
    stdout = result.stdout
    använda_uids = {int(rad.split(":")[2]) for rad in stdout.strip().split("\n") if rad}
    ny_uid = max(använda_uids) + 1
    return ny_uid


def skapa_användarkonto(användarnamn, lösenord, uid):
    hemkatalog = f"/home/{användarnamn}"

    # Skapa lokalt användarkonto
    subprocess.run(['useradd', '-u', str(uid), '-m', '-d', hemkatalog, användarnamn], check=True)
    print(f"Användarkonto '{användarnamn}' har skapats med hemkatalog: {hemkatalog} och UID: {uid}")

    # Lägg till användaren i LDAP
    subprocess.run(['ldapadduser', användarnamn, 'users', str(uid)], check=True)

    # Sätt lösenordet i LDAP
    subprocess.run(['ldappasswd', '-x', '-D', 'cn=admin,dc=allsh436,dc=example,dc=com',
                    '-w', 'password', '-s', lösenord,
                    f"uid={användarnamn},ou=people,dc=allsh436,dc=example,dc=com"], check=True)

    print(f"Användarkonto '{användarnamn}' skapades med lösenord '{lösenord}'.")

main()
