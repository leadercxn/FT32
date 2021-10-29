#! /usr/bin/env python
# -*- coding: utf-8 -*-

import sys

import subprocess
import re

JLINK_SCRIPT_READID = """device = %s
if SWD
speed 4000
mem8 %s 8
exit
"""

JLINK_SCRIPT_ERASE_CONFIG = """device = %s
if SWD
speed 4000
erase
r
g
exit
"""

JLINK_SCRIPT_LOAD_CONFIG = """device = %s
if SWD
speed 4000
loadfile %s %s
speed 4000
r
g
exit
"""

JLINK_SCRIPT_READ = """device = %s
if SWD
speed 4000
mem32 %s 20
exit
"""


class JlinkAPI(object):

    def __init__(self, deviceType):
        '''
        @param deviceType: 通过芯片类型选择不同的addr
        '''

        self.device = 'STM32F030C8'
        # self.device = 'NRF51822_XXAC'
        self.device_id_addr = '0x10000060'   
        self.load_addr = '0x00000'  

        self.jlink_commander = 'JLinkExe'
        if sys.platform.startswith('win32'):
            self.jlink_commander = 'JLink'

    def get_device_id(self):
        '''获取chip_id'''
        jlink_script_file_name = '/tmp/jlink_script_readid'
        with open(jlink_script_file_name, 'wr') as jlink_script_file:
            jlink_script_file.write(JLINK_SCRIPT_READID % (self.device, self.device_id_addr))

        cmd = '%s -CommandFile %s' %(self.jlink_commander, jlink_script_file_name)

        output = subprocess.check_output(cmd, shell=True)

        find_id = r'{} = (.+)'.format(self.device_id_addr[2:])
        rc = re.findall(find_id,output)
        if rc:
            return rc[0].replace(' ', '').upper()
        return None

    def load_config(self):

        config_file_name = 'ft32f0.bin'

        jlink_script_file_name = '/tmp/jlink_script_load_config'
        with open(jlink_script_file_name, 'wr') as jlink_script_file:
            jlink_script_file.write(JLINK_SCRIPT_LOAD_CONFIG %(self.device, config_file_name, self.load_addr))

        cmd = '%s -CommandFile %s' %(self.jlink_commander, jlink_script_file_name)

        output = subprocess.check_output(cmd, shell=True)
        print "\n------\load_config"
        print(output)

        return False

    def device_read(self):
        '''device_read'''
        jlink_script_file_name = '/tmp/jlink_script_read'
        with open(jlink_script_file_name, 'wr') as jlink_script_file:
            jlink_script_file.write(JLINK_SCRIPT_READ % (self.device, self.load_addr))

        cmd = '%s -CommandFile %s' %(self.jlink_commander, jlink_script_file_name)

        output = subprocess.check_output(cmd, shell=True)
        print "\n------\ndevice_read"
        print(output)

        return False

    def erase_config(self):

        jlink_script_file_name = '/tmp/jlink_script_erase_config'
        with open(jlink_script_file_name, 'wr') as jlink_script_file:
            jlink_script_file.write(JLINK_SCRIPT_ERASE_CONFIG %(self.device))

        cmd = '%s -CommandFile %s' %(self.jlink_commander, jlink_script_file_name)

        output = subprocess.check_output(cmd, shell=True)
        print "\n------\nwrite_config"
        print(output)

        return False

if __name__ == '__main__':
    api = JlinkAPI('chip_s')
    api.erase_config()
    api.load_config()
    # api.device_read()


