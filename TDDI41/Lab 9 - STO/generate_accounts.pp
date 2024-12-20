from unidecode import unidecode
import subprocess
import random
import string
import sys
import os

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

        subprocess.run(['ldapadduser', användarnamn, 'users'], check=True)

        subprocess.run([
            'ldappasswd', '-x',
            '-D', 'cn=admin,dc=allsh436,dc=example,dc=com',
            '-w', 'password',
            '-s', lösenord,
            f"uid={användarnamn},ou=people,dc=allsh436,dc=example,dc=com"
        ], check=True)

        uid = uid(användarnamn)

        hemkatalog_bas = random.choice(["/home1", "/home2"])
        server_hemkatalog = f"{hemkatalog_bas}/{användarnamn}"

        skapa_hemkatalog(server_hemkatalog, uid)
        skapa_automount_post(användarnamn, server_hemkatalog)

        print(f"Användarkonto '{användarnamn}' skapades med lösenord '{lösenord}'.")

    print("Alla användarkonton har skapats, hemkataloger skapade och automount-poster lagts till.")

def generera_användarnamn(namn):
    namn = unidecode(namn)
    initialer = ''.join([del_namn[:2] for del_namn in namn.lower().split()[:2] if del_namn[:2].isalnum()])
    slumpade_bokstäver = ''.join(random.choices(string.ascii_lowercase, k=2))
    nummer = random.randint(100, 999)
    användarnamn = f"{initialer}{slumpade_bokstäver}{nummer}"
    return användarnamn

def generera_lösenord():
    length = random.randint(5, 7)
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

def uid(användarnamn):
    result = subprocess.run([
        'ldapsearch', '-x', '-LLL',
        '-D', 'cn=admin,dc=allsh436,dc=example,dc=com',
        '-w', 'password',
        '-b', 'dc=allsh436,dc=example,dc=com',
        f'(uid={användarnamn})', 'uidNumber'
    ], capture_output=True, text=True, check=True)

    for rad in result.stdout.split('\n'):
        if rad.startswith('uidNumber:'):
            return int(rad.split(': ')[1])

def skapa_hemkatalog(hemkatalog, uid):
    os.makedirs(hemkatalog, exist_ok=True)
    os.chmod(hemkatalog, 0o700)
    os.chown(hemkatalog, uid, -1)  
    print(f"Hemkatalog skapad och rättigheter satta: {hemkatalog}")

def skapa_automount_post(användarnamn, server_hemkatalog):
    automount_dn = f"cn={användarnamn},ou=auto.home,ou=automount,ou=admin,dc=allsh436,dc=example,dc=com"
    automount_info = f"-fstype=nfs4,rw,sync,vers=4 10.0.0.2:{server_hemkatalog}" 

    ldif_entry = (
        f"dn: {automount_dn}\n"
        f"objectClass: automount\n"
        f"objectClass: top\n"
        f"cn: {användarnamn}\n"
        f"automountInformation: {automount_info}\n\n"
    )

    subprocess.run([
        'ldapadd', '-x',
        '-D', 'cn=admin,dc=allsh436,dc=example,dc=com',
        '-w', 'password'
    ], input=ldif_entry, text=True, check=True)

if __name__ == '__main__':
    main()
