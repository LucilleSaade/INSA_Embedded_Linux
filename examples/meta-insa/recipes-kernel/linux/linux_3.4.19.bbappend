FILESEXTRAPATHS_prepend_eukrea := "${THISDIR}/${P}:"

SRC_URI_append_eukrea-cpuimx51 = " file://0098-hack-to-free-screen-GPIO.patch \
				   file://0099-hack-to-free-led1-GPIO.patch "
