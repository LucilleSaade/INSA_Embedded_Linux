DESCRIPTION = "servo control tool"
LICENSE="GPLv2"
LIC_FILES_CHKSUM = "file://../servoctl.c;beginline=1;endline=17;md5=4b0530b0bdc457f17d58d594cc3991b0"

PR = "r0"

SRC_URI = "file://servoctl.c"

do_compile() {
	${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/servoctl.c -o servoctl
}

do_install() {
        install -m 0755 -d ${D}${bindir}
        install -m 0755 ${S}/servoctl ${D}${bindir}
}
