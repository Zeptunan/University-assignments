import subprocess
import unittest

class TestMachines(unittest.TestCase):
    def run_command(self, command):
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return result.stdout.strip()

    def test_ntp_status(self):
        stdout = self.run_command("systemctl is-active ntp")
        self.assertIn("active", stdout, "NTP service is not active")

    def test_ntp_config(self):
        stdout = self.run_command("cat /etc/ntp.conf")
        self.assertIn("server 10.0.0.1 iburst", stdout, "NTP configuration is incorrect.")

    def test_ntp_port(self):
        stdout = self.run_command("nft list ruleset | grep 'udp dport 123 accept'")
        self.assertTrue(stdout, "NTP is not allowed on UDP port 123 in nftables")

    def test_ntp_synced(self):
        stdout = self.run_command("ntpq -p")
        self.assertIn("*gw.allsh436.exa", stdout, "Client is not synced with the NTP server.")

    def test_ntp_query(self):
        stdout = self.run_command("ntpdate -q 10.0.0.1")
        self.assertIn("server 10.0.0.1", stdout, "NTP query failed")

    def test_server_time_margins(self):
        stdout = self.run_command("ntpstat")
        self.assertIn("synchronised to NTP server", stdout, "NTP server is not synchronized")
    
        if "time correct to within" in stdout:
            correct_line = next(line for line in stdout.splitlines() if "time correct to within" in line)
            margin = float(correct_line.split()[4])  
            self.assertLessEqual(margin, 100, "Time margin too high")
        else:
            self.fail("Time margin information not found in ntpstat output")


if __name__ == '__main__':
    unittest.main()
