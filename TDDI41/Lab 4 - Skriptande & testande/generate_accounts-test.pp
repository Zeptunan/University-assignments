file = open('/etc/passwd', 'r') 
lines = file.readlines() 
users = [line.split(':')[0] for line in lines] 


def test_root():
    assert 'root' in users


def test_noshell():
    for line in lines:
        if line.split(':')[0] == 'games': 
            assert line.split(':')[-1].strip() == '/usr/sbin/nologin' 
