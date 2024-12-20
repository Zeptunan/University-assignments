import subprocess
import unittest

class TestMachines(unittest.TestCase):
    def run_command(self, command, stdout=subprocess.PIPE, stderr=subprocess.PIPE):
        result = subprocess.run(command, shell=True, stdout=stdout, stderr=stderr)
        return result.stdout.decode('utf-8'), result.stderr.decode('utf-8'), result.returncode

    def test_nameserver_resolution(self):
        stdout, stderr, returncode = self.run_command("dig @10.0.0.2 example.com +short")
        self.assertEqual(returncode, 0, f"dig command failed")
        self.assertEqual("93.184.215.14", stdout.strip(), "DNS server did not resolve example.com correctly")

    def test_nameserver_config(self):
        stdout, stderr, returncode = self.run_command("cat /etc/resolv.conf")
        self.assertEqual(returncode, 0, f"cat command failed")
        self.assertIn("nameserver 10.0.0.2", stdout, "DNS server is not set to 10.0.0.2")

if __name__ == '__main__':
    unittest.main()    