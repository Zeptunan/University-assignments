import subprocess
import unittest
import os

class TestServer(unittest.TestCase):
    def run_command(self, command):
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return result.stdout.strip()

#####################################################################################################
# RAID tester
    def test_raid1_configuration(self):
        stdout = self.run_command("cat /proc/mdstat")
        self.assertIn("md0", stdout, "RAID-1 (md0) är inte konfigurerat")
        self.assertIn("[raid1]", stdout, "RAID-1 (md0) does not have the correct RAID type")
        self.assertIn("[UU]", stdout, "RAID-1 (md0) is not fully synchronized")
        self.assertIn("[2/2]", stdout, "RAID-1 (md0) is not fully synchronized")

    def test_raid0_configuration(self):
        stdout = self.run_command("cat /proc/mdstat")
        self.assertIn("md1", stdout, "RAID-0 (md1) is not configured")
        self.assertIn("[raid0]", stdout, "RAID-0 (md1) does not have the correct RAID type")

#######################################################################################################
# LVM tester
    def test_lvm_PV(self):
        stdout = self.run_command("pvdisplay")
        self.assertIn("/dev/md0", stdout, "Physical volume /dev/md0 missing")
        self.assertIn("/dev/md1", stdout, "Physical volume /dev/md1 missing")
        self.assertIn("vgvirt", stdout, "Volume group vgvirt missing")

    def test_lvm_volumes(self):
        stdout = self.run_command("df -h")
        self.assertIn("/home1", stdout, "Logical volume for /home1 is not mounted")
        self.assertIn("/home2", stdout, "Logical volume for /home2 is not mounted")
        
    def test_fstab_entries(self):
        stdout = self.run_command("cat /etc/fstab")
        self.assertIn("/dev/vgvirt/lvvol1", stdout, "Logical volume lvvol1 is not in /etc/fstab")
        self.assertIn("/home1", stdout, "Mount point /home1 is not in /etc/fstab")
        self.assertIn("/dev/vgvirt/lvvol2", stdout, "Logical volume lvvol2 is not in /etc/fstab")
        self.assertIn("/home2", stdout, "Mount point /home2 is not in /etc/fstab")
        self.assertIn("ext4", stdout, "Logical volumes are not using ext4 in /etc/fstab")

########################################################################################################
# Automount/NFS tester
    def test_nfs_service_active(self):
        stdout = self.run_command("systemctl is-active nfs-kernel-server")
        self.assertIn("active", stdout, "NFS service is not active")

    def test_autofs_active(self):
        stdout = self.run_command("systemctl is-active autofs")
        self.assertIn("active", stdout, "Autofs-tjänsten är inte aktiv på klienten.")

    def test_nfs_tcp_port(self):
        stdout = self.run_command("nft list ruleset | grep 'tcp dport 2049 accept'")
        self.assertTrue(stdout, "NFS is not allowed on tcp port 2049 in nftables")

    def test_nfs_udp_port(self):
        stdout = self.run_command("nft list ruleset | grep 'udp dport 2049 accept'")
        self.assertTrue(stdout, "NFS is not allowed on udp port 2049 in nftables")
    
    # Vilka kataloger exporteras till vilka klienter
    # Med vilka rättigheter exporteras olika kataloger
    def test_exportfs_v(self):
        stdout = self.run_command("exportfs -v")
        
        self.assertIn("/usr/local", stdout, "Expected /usr/local to be exported")
        self.assertIn("10.0.0.0/24", stdout, "Expected /usr/local to be exported to 10.0.0.0/24")
        self.assertIn("rw", stdout, "Expected /usr/local to be exported with rw permissions")

        self.assertIn("/home1", stdout, "Expected /home1 to be exported")
        self.assertIn("10.0.0.3", stdout, "Expected /home1 to be exported to 10.0.0.3")
        self.assertIn("10.0.0.4", stdout, "Expected /home1 to be exported to 10.0.0.4")
        self.assertIn("rw", stdout, "Expected /home1 to be exported with rw permissions")
    
        self.assertIn("/home2", stdout, "Expected /home2 to be exported")
        self.assertIn("10.0.0.3", stdout, "Expected /home2 to be exported to 10.0.0.3")
        self.assertIn("10.0.0.4", stdout, "Expected /home2 to be exported to 10.0.0.4")
        self.assertIn("rw", stdout, "Expected /home2 to be exported with rw permissions")


    def test_services_restart(self):
        for service in ["nfs-kernel-server", "autofs"]:
            stdout = self.run_command(f"systemctl is-enabled {service}")
            self.assertIn(stdout, ["enabled", "alias"], f"Service {service} is not set to start on boot")

                
if __name__ == '__main__':
    unittest.main()
