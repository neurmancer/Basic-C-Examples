CC ?= cc
CFLAGS ?= -O2 -g
CPPFLAGS += -D_DEFAULT_SOURCE -DNORMALUNIX -DLINUX -DDOOMGENERIC_RESX=320 -DDOOMGENERIC_RESY=200 -I.engine/doomgeneric
LDLIBS += -lm
ENGINE_REV = dcb7a8dbc7a16ce3dda29382ac9aae9d77d21284
ENGINE_OBJECTS = dummy.o am_map.o doomdef.o doomstat.o dstrings.o d_event.o d_items.o d_iwad.o d_loop.o d_main.o d_mode.o d_net.o f_finale.o f_wipe.o g_game.o hu_lib.o hu_stuff.o info.o i_cdmus.o i_endoom.o i_joystick.o i_scale.o i_sound.o i_system.o i_timer.o memio.o m_argv.o m_bbox.o m_cheat.o m_config.o m_controls.o m_fixed.o m_menu.o m_misc.o m_random.o p_ceilng.o p_doors.o p_enemy.o p_floor.o p_inter.o p_lights.o p_map.o p_maputl.o p_mobj.o p_plats.o p_pspr.o p_saveg.o p_setup.o p_sight.o p_spec.o p_switch.o p_telept.o p_tick.o p_user.o r_bsp.o r_data.o r_draw.o r_main.o r_plane.o r_segs.o r_sky.o r_things.o sha1.o sounds.o statdump.o st_lib.o st_stuff.o s_sound.o tables.o v_video.o wi_stuff.o w_checksum.o w_file.o w_main.o w_wad.o z_zone.o w_file_stdc.o i_input.o i_video.o doomgeneric.o
OBJECTS = $(addprefix build/,$(ENGINE_OBJECTS)) build/doomgeneric_terminal.o

.PHONY: all fetch clean test
all: terminal-doom

fetch:
	git clone https://github.com/ozkl/doomgeneric.git .engine
	git -C .engine checkout --detach $(ENGINE_REV)

.engine/doomgeneric/doomgeneric.h:
	@echo 'Engine missing. Run make fetch first.' >&2
	@exit 1

$(OBJECTS): .engine/doomgeneric/doomgeneric.h Makefile | build

build:
	mkdir -p build

build/doomgeneric_terminal.o: doomgeneric_terminal.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -std=c11 -Wall -Wextra -Wpedantic -Werror -MMD -MP -c $< -o $@

build/%.o: .engine/doomgeneric/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

terminal-doom: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LDLIBS) -o $@

clean:
	rm -rf build terminal-doom

-include $(OBJECTS:.o=.d)
