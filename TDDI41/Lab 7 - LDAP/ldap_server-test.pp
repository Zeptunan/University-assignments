import subprocess
import unittest

class TestMachines(unittest.TestCase):
    def run_command(self, command):
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return result.stdout, result.returncode

    def test_slapd_running(self):
        stdout, returncode = self.run_command("systemctl is-active slapd")
        self.assertIn("active", stdout.strip(), "slapd is not active")

    def test_server_dn(self):
        stdout, returncode = self.run_command("ldapsearch -x -LLL uid=user1")
        self.assertIn("dn: uid=user1", stdout, "Specific user 'user1' not found in LDAP")

    def test_ldap_port_open(self):
        stdout, returncode = self.run_command("nft list ruleset")
        self.assertIn("tcp dport 389", stdout, "TCP port 389 for LDAP is not open in nftables")


if __name__ == '__main__':
    unittest.main()    