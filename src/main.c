#include <sdl2/SDL.h>
#include <string.h>

#include "GLOBAL.h"
#include "renderer.h"
#include "util.h"
#include "str.h"

static I32 ww = 55555;
static I32 wh = 55555;

static const char button_map[256] = {
	[ SDL_BUTTON_LEFT   & 0xff ] =  MU_MOUSE_LEFT,
	[ SDL_BUTTON_RIGHT  & 0xff ] =  MU_MOUSE_RIGHT,
	[ SDL_BUTTON_MIDDLE & 0xff ] =  MU_MOUSE_MIDDLE,
};

static const char key_map[256] = {
	[ SDLK_LSHIFT       & 0xff ] = MU_KEY_SHIFT,
	[ SDLK_RSHIFT       & 0xff ] = MU_KEY_SHIFT,
	[ SDLK_LCTRL        & 0xff ] = MU_KEY_CTRL,
	[ SDLK_RCTRL        & 0xff ] = MU_KEY_CTRL,
	[ SDLK_LALT         & 0xff ] = MU_KEY_ALT,
	[ SDLK_RALT         & 0xff ] = MU_KEY_ALT,
	[ SDLK_RETURN       & 0xff ] = MU_KEY_RETURN,
	[ SDLK_BACKSPACE    & 0xff ] = MU_KEY_BACKSPACE,
};

static int textWidth(mu_Font font, const char *text, int len) {
	if (len == -1) { len = strLen(text); }
	return r_get_text_width(text, len);
}

static int textHeight(mu_Font font) {
	return r_get_text_height();
}

static void styleWindow(mu_Context* ctx) {
	static struct { const char* label; int idx; } colors[] = {
		{ "text:",         MU_COLOR_TEXT        },
		{ "border:",       MU_COLOR_BORDER      },
		{ "windowbg:",     MU_COLOR_WINDOWBG    },
		{ "titlebg:",      MU_COLOR_TITLEBG     },
		{ "titletext:",    MU_COLOR_TITLETEXT   },
		{ "panelbg:",      MU_COLOR_PANELBG     },
		{ "button:",       MU_COLOR_BUTTON      },
		{ "buttonhover:",  MU_COLOR_BUTTONHOVER },
		{ "buttonfocus:",  MU_COLOR_BUTTONFOCUS },
		{ "base:",         MU_COLOR_BASE        },
		{ "basehover:",    MU_COLOR_BASEHOVER   },
		{ "basefocus:",    MU_COLOR_BASEFOCUS   },
		{ "scrollbase:",   MU_COLOR_SCROLLBASE  },
		{ "scrollthumb:",  MU_COLOR_SCROLLTHUMB },
		{ NULL }
	};
}

static char b[4096];

static void windowUi(mu_Context* ctx) {
	if (mu_begin_window_ex(ctx, "CAS", mu_rect(0, 0, ww, wh), MU_OPT_NOCLOSE | MU_OPT_NOTITLE)) {
		mu_layout_row(ctx, 3, (int[]) {220, 60}, 0);

		mu_textbox_ex(ctx, b, 4069, 0);
		if (mu_button(ctx, "Submit")) {
			char a[strLen(b)];
			strcpy(a, b);
			PRINTF("%s\n", b);
			for (U16 i = 0; i < strLen(b); ++i)
				b[i] = 0;
		}
		mu_end_window(ctx);
	}
}


static void processFrame(mu_Context *ctx) {
	mu_begin(ctx);
	styleWindow(ctx);
	windowUi(ctx);
	mu_end(ctx);
}


MAIN {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		PRINTF("Failed to init video. Error: %s\n", SDL_GetError());
	}
	r_init();
	mu_Context* ctx = malloc(sizeof(mu_Context));
	mu_init(ctx);
	ctx->text_width = textWidth;
	ctx->text_height = textHeight;

	U8 running = 1;
	SDL_Event ev;
	do {
		// Event
		while (SDL_PollEvent(&ev)) {
			switch (ev.type) {
				case SDL_QUIT: exit(EXIT_SUCCESS); break;
				case SDL_MOUSEMOTION: mu_input_mousemove(ctx, ev.motion.x, ev.motion.y); break;
				case SDL_MOUSEWHEEL: mu_input_scroll(ctx, 0, ev.wheel.y * -30); break;
				case SDL_TEXTINPUT: mu_input_text(ctx, ev.text.text); break;

				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP: {
					int b = button_map[ev.button.button & 0xff];
					if (b && ev.type == SDL_MOUSEBUTTONDOWN) { mu_input_mousedown(ctx, ev.button.x, ev.button.y, b); }
					if (b && ev.type ==   SDL_MOUSEBUTTONUP) { mu_input_mouseup(ctx, ev.button.x, ev.button.y, b);   }
					break;
				}

				case SDL_KEYDOWN:
				case SDL_KEYUP: {
					int c = key_map[ev.key.keysym.sym & 0xff];
					if (c && ev.type == SDL_KEYDOWN) { mu_input_keydown(ctx, c); }
					if (c && ev.type ==   SDL_KEYUP) { mu_input_keyup(ctx, c);   }
					break;
				}
				case SDL_WINDOWEVENT_RESIZED:
					rSetDims(ev.window.data1, ev.window.data2);
					break;
				default:
					break;
			}
		}
		// Render
		processFrame(ctx);
		r_clear(mu_color(0, 0, 0, 255));
		mu_Command *cmd = NULL;
		while (mu_next_command(ctx, &cmd)) {
			switch (cmd->type) {
				case MU_COMMAND_TEXT: r_draw_text(cmd->text.str, cmd->text.pos, cmd->text.color); break;
				case MU_COMMAND_RECT: r_draw_rect(cmd->rect.rect, cmd->rect.color); break;
				case MU_COMMAND_ICON: r_draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color); break;
				case MU_COMMAND_CLIP: r_set_clip_rect(cmd->clip.rect); break;
			}
		}
		r_present();

	} while (running == 1);

	free(ctx);
	return 0;
}

