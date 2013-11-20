DESCRIPTION = "servo control tool"
LICENSE="GPLv2"
LIC_FILES_CHKSUM = "file://../servoctl.c;beginline=1;endline=17;md5=2eefc827593fa1fcd83414f1f8773f47"

PR = "r0"

SRC_URI = "file://servoctl.c"

do_compile() {
	${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/servoctl.c -o servoctl
}

do_install() {
        install -m 0755 -d ${D}${bindir}
        install -m 0755 ${S}/servoctl ${D}${bindir}
}
