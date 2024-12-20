import subprocess
import unittest

class TestMachines(unittest.TestCase):
    def run_command(self, command):
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return result.stdout, result.returncode

    def test_nslcd_running(self):
        stdout, returncode = self.run_command("systemctl is-active nslcd")
        self.assertIn("active", stdout.strip(), "nslcd is not active")

    def test_nscd_running(self):
        stdout, returncode = self.run_command("systemctl is-active nscd")
        self.assertIn("active", stdout.strip(), "nscd is not active")

    def test_nsswitch_conf(self):
        stdout, returncode = self.run_command("getent passwd user1")
        self.assertIn("user1:", stdout.strip(), "passwd is not configured correctly: user1 not found in LDAP")

    def test_client_dn(self):
        stdout, returncode = self.run_command("ldapsearch -x -LLL dn")
        self.assertEqual(returncode, 0, "ldapsearch command failed")
        self.assertIn("dn: ", stdout.strip(), "No entries found in LDAP search")

if __name__ == '__main__':
    unittest.main()    