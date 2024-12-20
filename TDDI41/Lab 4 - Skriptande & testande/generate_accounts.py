from unidecode import unidecode
import subprocess # För att köra useradd och chpasswd
import random # För att generera slumpmässiga bokstäver
import string # För ascii_letters och digits 
import sys # För alla systemargument

def main():
    # Kontrollera att användaren angett exakt 2 argument (programmet och filnamnet)
    if len(sys.argv) != 2:
        print("Användning: python3 ./generate_accounts.py <filnamn>")  
        sys.exit(1)  

    filnamn = sys.argv[1]  # Hämta filnamnet som angavs som argument.
    
    # Öppna filen och läs varje rad, filtrera bort tomma rader
    with open(filnamn, 'r') as f:
        namn_list = [namn.strip() for namn in f if namn.strip()]  # Ta bort extra mellanslag och hoppa över tomma rader.

    # Iterera över varje namn i listan
    for namn in namn_list:
        användarnamn = generera_användarnamn(namn)  
        lösenord = generera_lösenord()  

        skapa_användarkonto(användarnamn, lösenord)  

    print("Alla användarkonton har skapats.")  

def generera_användarnamn(namn):
    namn = unidecode(namn)  # Omvandla namnet till ASCII-tecken
    initialer = ''.join([del_namn[:2] for del_namn in namn.lower().split()[:2] if del_namn[:2].isalnum()])  # Tar de två första bokstäverna från för- och efternamn.
    slumpade_bokstäver = ''.join(random.choices(string.ascii_lowercase, k=2))  
    nummer = random.randint(100, 999)  
    användarnamn = f"{initialer}{slumpade_bokstäver}{nummer}"  

    print(f"Ditt användarnamn är: {användarnamn}")  
    return användarnamn  

def generera_lösenord():
    length = random.randint(5, 7)  # Välj en slumpmässig längd mellan 5 och 7 tecken.
    lösenord = ''.join(random.choices(string.ascii_letters + string.digits, k=length))  
    
    print(f"Ditt lösenord är: {lösenord}") 
    return lösenord 

def skapa_användarkonto(användarnamn, lösenord):
    hemkatalog = f"/home/{användarnamn}"  # Skapa en hemkatalog baserat på användarnamnet.

    # Skapa ett användarkonto och hemkatalog med useradd-kommandot
    subprocess.run(['useradd', '-m', '-d', hemkatalog, användarnamn])  
    print(f"Användarkonto '{användarnamn}' har skapats med hemkatalog: {hemkatalog}") 

    # Sätt lösenord för användaren med chpasswd-kommandot
    subprocess.run(['chpasswd'], input=f"{användarnamn}:{lösenord}", text=True) 

main()
