file = open('/etc/passwd', 'r') # Öppnar systemfilen /etc/passwd i läsläge.
lines = file.readlines() # Läser alla rader i filen och sparar dem i en lista som heter 'lines'.
users = [line.split(':')[0] for line in lines] # Skapar en lista med alla användarnamn i systemet.


def test_root():
    assert 'root' in users # Kontrollerar att användaren "root" finns i listan 'users'.


def test_noshell():
    for line in lines:
        if line.split(':')[0] == 'games': # Om användarnamnet "games" hittas i filen...
            assert line.split(':')[-1].strip() == '/usr/sbin/nologin' # Kontrollera att skalet är /usr/sbin/nologin.
