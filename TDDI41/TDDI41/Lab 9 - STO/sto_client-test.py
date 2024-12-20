import subprocess
import unittest

class TestMachines(unittest.TestCase):
    def run_command(self, command):
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return result.stdout.strip()  

    def test_autofs_active(self):
        stdout = self.run_command("systemctl is-active autofs")
        self.assertIn("active", stdout, "Autofs-tjänsten är inte aktiv på klienten.")

    def test_nfs_port_tcp(self):
        stdout = self.run_command("nft list ruleset | grep 'tcp dport 2049 accept' || true")
        self.assertTrue(stdout, "NFS is not allowed on tcp port 2049 in nftables")

    def test_nfs_port_udp(self):
        stdout = self.run_command("nft list ruleset | grep 'udp dport 2049 accept' || true")
        self.assertTrue(stdout, "NFS is not allowed on udp port 2049 in nftables")

    def test_automount_ldap_nsswitch(self):
        stdout = self.run_command("grep '^automount:' /etc/nsswitch.conf || true")
        self.assertIn("files ldap", stdout, "Klienten använder inte LDAP för automount enligt nsswitch.conf.")

    # Monteras /usr/local in vid uppstart (boot)
    def test_usr_local_boot_mount(self):
        stdout = self.run_command("cat /etc/fstab")
        expected_line = "10.0.0.2:/usr/local  /mnt/nfs_local  nfs4"
        self.assertIn(expected_line, stdout, f"Expected mount line '{expected_line}' not found in /etc/fstab")

    def test_usr_local_mounted(self):
        stdout = self.run_command("df -h")
        expected_line = "10.0.0.2:/usr/local"
        self.assertIn(expected_line, stdout, f"{expected_line} är inte korrekt monterat på klienten")

    def test_user1_home_mounted(self):
        stdout = self.run_command("su - user1 -c 'echo $HOME'")
        self.assertIn("/home/user1", stdout, "Hemkatalogen för user1 är inte korrekt monterad.")

    # Används LDAP för auto.master
    def test_automount_maps(self):
        stdout = self.run_command("automount -m")
        self.assertIn("/home", stdout, "Automount för /home är inte konfigurerat korrekt.")
        self.assertIn("map: ldap:", stdout, "Automount använder inte LDAP som källa för kartor.")

if __name__ == '__main__':
    unittest.main()
