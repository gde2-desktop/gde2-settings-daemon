NULL =

AM_CPPFLAGS = \
	-DDATADIR=\""$(datadir)"\"				\
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\"	\
	-DLIBEXECDIR=\""$(libexecdir)"\" 			\
	-DGDE2_SETTINGS_PLUGINDIR=\""$(plugindir)"\"		\
	$(WARN_CFLAGS)						\
	$(DISABLE_DEPRECATED_CFLAGS)				\
	$(SETTINGS_DAEMON_CFLAGS)				\
	$(LIBNOTIFY_CFLAGS)						\
	$(NULL)

noinst_LTLIBRARIES = 			\
	libmsd-profile.la		\
	$(NULL)

libmsd_profile_la_SOURCES =		\
	gde2-settings-profile.c	\
	gde2-settings-profile.h	\
	$(NULL)

libmsd_profile_la_CPPFLAGS = 		\
	$(AM_CPPFLAGS)
	$(DISABLE_DEPRECATED_CFLAGS)	\
	$(NULL)

libmsd_profile_la_CFLAGS =		\
	$(SIMPLE_GREETER_CFLAGS)	\
	$(NULL)

libmsd_profile_la_LIBADD =		\
	$(NULL)

libmsd_profile_la_LDFLAGS = 	\
	-export-dynamic 	\
	$(NULL)

msddir = $(libexecdir)

msd_PROGRAMS = \
	gde2-settings-daemon

gde2-settings-manager-glue.h: gde2-settings-manager.xml Makefile.am
	$(AM_V_GEN) dbus-binding-tool --prefix=gde2_settings_manager --mode=glib-server $< > $@

gde2-settings-client.h: gde2-settings-manager.xml Makefile.am
	$(AM_V_GEN) dbus-binding-tool --prefix=gde2_settings_manager --mode=glib-client $< > $@

BUILT_SOURCES = 			\
	gde2-settings-manager-glue.h	\
	gde2-settings-client.h		\
	$(NULL)

apidir   = $(includedir)/gde2-settings-daemon
api_DATA = 				\
	gde2-settings-client.h		\
	gde2-settings-plugin.h

gde2_settings_daemon_SOURCES =		\
	main.c				\
	gde2-settings-manager.c	\
	gde2-settings-manager.h	\
	gde2-settings-plugin.c		\
	gde2-settings-plugin.h		\
	gde2-settings-plugin-info.c	\
	gde2-settings-plugin-info.h	\
	gde2-settings-module.c		\
	gde2-settings-module.h		\
	$(NULL)

gde2_settings_daemon_CPPFLAGS = \
	$(AM_CPPFLAGS)

gde2_settings_daemon_CFLAGS = 		\
	$(GDE2_DESKTOP_CFLAGS)          \
	$(AM_CFLAGS)

gde2_settings_daemon_LDFLAGS = 	\
	$(AM_LDFLAGS)

gde2_settings_daemon_LDADD = 		\
	libmsd-profile.la		\
	$(SETTINGS_DAEMON_LIBS)	\
	$(GDE2_DESKTOP_LIBS)    \
	$(LIBNOTIFY_LIBS)

EXTRA_DIST = 				\
	$(Dbusapi_DATA)			\
	gde2-settings-manager.xml	\
	$(NULL)

CLEANFILES = 				\
	$(BUILT_SOURCES)		\
	$(NULL)


# vim: ts=8
