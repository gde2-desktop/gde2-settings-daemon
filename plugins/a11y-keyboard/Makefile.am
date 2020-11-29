NULL =

gtkbuilderdir = $(pkgdatadir)
gtkbuilder_DATA = 			\
	msd-a11y-preferences-dialog.ui	\
	$(NULL)

noinst_PROGRAMS =				\
	test-a11y-preferences-dialog		\
	$(NULL)

test_a11y_preferences_dialog_SOURCES =		\
	msd-a11y-preferences-dialog.c		\
	msd-a11y-preferences-dialog.h		\
	test-a11y-preferences-dialog.c		\
	$(NULL)

test_a11y_preferences_dialog_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon			\
	-DPIXMAPDIR=\""$(pkgdatadir)"\"				\
	-DGTKBUILDERDIR=\""$(pkgdatadir)"\"				\
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\"	\
	$(AM_CPPFLAGS)

test_a11y_preferences_dialog_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(AM_CFLAGS)

test_a11y_preferences_dialog_LDADD = \
	$(SETTINGS_DAEMON_LIBS)			\
	$(SETTINGS_PLUGIN_LIBS)			\
	$(NULL)

plugin_LTLIBRARIES = \
	liba11y-keyboard.la		\
	$(NULL)

liba11y_keyboard_la_SOURCES = 		\
	msd-a11y-keyboard-plugin.h	\
	msd-a11y-keyboard-plugin.c	\
	msd-a11y-keyboard-manager.h	\
	msd-a11y-keyboard-manager.c	\
	msd-a11y-preferences-dialog.h	\
	msd-a11y-preferences-dialog.c	\
	$(NULL)

liba11y_keyboard_la_CPPFLAGS = \
	-I$(top_srcdir)/gde2-settings-daemon		\
	-DGDE2_SETTINGS_LOCALEDIR=\""$(datadir)/locale"\" \
	-DGTKBUILDERDIR=\""$(gtkbuilderdir)"\" \
	$(AM_CPPFLAGS)

liba11y_keyboard_la_CFLAGS = \
	$(SETTINGS_PLUGIN_CFLAGS)	\
	$(LIBNOTIFY_CFLAGS)		\
	$(AM_CFLAGS)

liba11y_keyboard_la_LDFLAGS = 		\
	$(MSD_PLUGIN_LDFLAGS)		\
	$(NULL)

liba11y_keyboard_la_LIBADD  = 		\
	$(SETTINGS_PLUGIN_LIBS)		\
	$(XF86MISC_LIBS)		\
	$(LIBNOTIFY_LIBS)		\
	$(NULL)

plugin_in_files = 		\
	a11y-keyboard.gde2-settings-plugin.in	\
	$(NULL)

plugin_DATA = $(plugin_in_files:.gde2-settings-plugin.in=.gde2-settings-plugin)

EXTRA_DIST = 			\
	$(plugin_in_files)	\
	$(gtkbuilder_DATA)		\
	$(NULL)

CLEANFILES = 			\
	$(plugin_DATA)		\
	$(NULL)

DISTCLEANFILES =		\
	$(plugin_DATA)		\
	$(NULL)

@MSD_INTLTOOL_PLUGIN_RULE@
