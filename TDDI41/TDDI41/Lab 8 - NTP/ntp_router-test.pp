import subprocess
import unittest

class TestRouter(unittest.TestCase):
    def run_command(self, command):
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return result.stdout.strip()

    def test_ntp_status(self):
        stdout = self.run_command("systemctl is-active ntp")
        self.assertIn("active", stdout, "NTP service is not active")

    def test_ntp_config_pool(self):
        stdout = self.run_command("cat /etc/ntp.conf")
        self.assertIn("pool se.pool.ntp.org iburst", stdout, "NTP pool configuration is incorrect")

    def test_ntp_config_peer(self):
        stdout = self.run_command("cat /etc/ntp.conf")
        self.assertIn("restrict 10.0.0.0/24 mask 255.255.255.0 nopeer", stdout, "NTP configuration is incorrect")

    def test_ntp_port(self):
        stdout = self.run_command("nft list ruleset | grep 'udp dport 123 accept'")
        self.assertTrue(stdout, "NTP is not allowed on UDP port 123 in nftables")

    def test_ntp_synced(self):
        stdout = self.run_command("ntpq -p")
        self.assertIn("*", stdout, "Router is not synced with any NTP server")

if __name__ == '__main__':
    unittest.main()

 