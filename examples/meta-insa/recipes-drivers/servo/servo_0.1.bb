DESCRIPTION = "Servo kernel module and tool to control it"
LICENSE="GPLv2"
LIC_FILES_CHKSUM = "file://LICENSE;md5=5036eb4ff8874567b5c7c1de38ee3046"

PR = "r0"

SRC_URI = "file://servo.c \
	   file://Makefile \
	   file://LICENSE"

S = "${WORKDIR}"

inherit module

do_compile () {
	unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS CC LD CPP
	oe_runmake 'MODPATH="${D}${base_libdir}/modules/${KERNEL_VERSION}/kernel/drivers"' \
		'KERNEL_SOURCE="${STAGING_KERNEL_DIR}"' \
		'KDIR="${STAGING_KERNEL_DIR}"' \
		'KERNEL_VERSION="${KERNEL_VERSION}"' \
		'CC="${KERNEL_CC}"' \
		'LD="${KERNEL_LD}"'

}

FILE_${PN} += " /usr/bin/servoctl "

do_install () {
	install -d ${D}${base_libdir}/modules/${KERNEL_VERSION}/kernel/drivers
	install -m 0644 ${S}/servo*${KERNEL_OBJECT_SUFFIX} ${D}${base_libdir}/modules/${KERNEL_VERSION}/kernel/drivers
}

