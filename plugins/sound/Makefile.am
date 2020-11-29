plugin_LTLIBRARIES = \
	libsound.la

libsound_la_SOURCES = \
	msd-sound-plugin.h \
	msd-sound-plugin.c \
	msd-sound-manager.h \
	msd-sound-manager.c

libsound_la_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon \
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	$(AM_CPPFLAGS)

libsound_la_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS) \
	$(GDE2_CFLAGS)	\
	$(PULSE_CFLAGS)	\
	$(AM_CFLAGS)

libsound_la_LDFLAGS = \
	$(MSD_PLUGIN_LDFLAGS)

libsound_la_LIBADD = \
	$(SETTINGS_PLUGIN_LIBS)	\
	$(PULSE_LIBS)

plugin_in_files = \
	sound.gde2-settings-plugin.in

plugin_DATA = $(plugin_in_files:.gde2-settings-plugin.in=.gde2-settings-plugin)

EXTRA_DIST = \
	$(plugin_in_files)

CLEANFILES = \
	$(plugin_DATA)

DISTCLEANFILES = \
	$(plugin_DATA)

@MSD_INTLTOOL_PLUGIN_RULE@
