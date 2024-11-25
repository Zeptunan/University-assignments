import subprocess
import unittest

class TestDNSServer(unittest.TestCase):
    def run_command(self, command, stdout=subprocess.PIPE, stderr=subprocess.PIPE):
        result = subprocess.run(command, shell=True, stdout=stdout, stderr=stderr)
        return result.stdout.decode('utf-8'), result.stderr.decode('utf-8'), result.returncode

    def test_bind9_conf(self):
        stdout, stderr, returncode = self.run_command("named-checkconf")
        self.assertEqual(returncode, 0, f"named-checkconf failed with error: {stderr}")
        
    def test_bind9_zone(self):
        stdout, stderr, returncode = self.run_command("named-checkzone allsh436.example.com /etc/bind/db.allsh436.example.com")
        self.assertEqual(returncode, 0, f"named-checkzone failed with error: {stderr}")

    def test_bind9_active(self):
        stdout, stderr, returncode = self.run_command("systemctl is-active bind9")
        self.assertEqual(returncode, 0, f"service is not active")
        self.assertEqual(stdout.strip(), "active", "bind9 service is not running as expected")

    def test_named_respond_correctly(self):
        stdout, stderr, returncode = self.run_command("dig @localhost google.com")
        self.assertEqual(returncode, 0, f"dig command failed: {stderr}")
        self.assertIn("ANSWER SECTION", stdout, "DNS server did not return an answer section")

    def test_forward_lookup(self):
        stdout, stderr, returncode = self.run_command("dig @localhost server.allsh436.example.com +short")
        self.assertEqual(returncode, 0, f"dig command failed: {stderr}")
        self.assertIn("10.0.0.2", stdout, "Forward lookup did not return the expected IP address for server")

    def test_reverse_lookup(self):
        stdout, stderr, returncode = self.run_command("dig @localhost -x 10.0.0.2 +short")
        self.assertEqual(returncode, 0, f"dig command failed: {stderr}")
        self.assertIn("server.allsh436.example.com", stdout, "Reverse lookup did not return the expected hostname for 10.0.0.2")

if __name__ == '__main__':
    unittest.main()  