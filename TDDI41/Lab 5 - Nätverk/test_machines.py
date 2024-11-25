import subprocess
import unittest

class TestNätverksMaskiner(unittest.TestCase):
    def run_command(self, command):
        result = subprocess.run(command, shell=True)
        return result.returncode

    def test_IP(self):
        self.assertEqual(self.run_command('cat /etc/network/interfaces | grep 10.0.0.4'), 0)

    def test_Network(self):
        self.assertEqual(self.run_command('cat /etc/network/interfaces | grep 255.255.255.0'), 0)

    def test_Gateway(self):
        self.assertEqual(self.run_command('cat /etc/network/interfaces | grep 10.0.0.1'), 0)

    def test_hostname(self):
        self.assertEqual(self.run_command('cat /etc/hostname | grep client-2'), 0)

    def test_reach_router(self):
        self.assertEqual(self.run_command('ping 10.0.0.1 -c 1'), 0)

    def test_reach_internet(self):
        self.assertEqual(self.run_command('ping google.com -c 1'), 0)

if __name__ == '__main__':
    unittest.main()
