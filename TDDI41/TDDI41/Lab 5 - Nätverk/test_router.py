import subprocess
import unittest

class TestRouter(unittest.TestCase):
    def run_command(self, command):
        result = subprocess.run(command, shell=True)
        return result.returncode

    def test_ping(self):
        self.assertEqual(self.run_command("ping -c 1 10.0.2.2"), 0)

    def test_ip_forwarding(self):
        with open("/proc/sys/net/ipv4/ip_forward", "r") as f:
            self.assertEqual(f.read().strip(), "1")

    def test_masquerade(self):
        result = subprocess.run("nft list ruleset", shell=True, stdout=subprocess.PIPE, text=True)
        self.assertIn("oifname \"ens3\" masquerade", result.stdout)

if __name__ == "__main__":
    unittest.main()

