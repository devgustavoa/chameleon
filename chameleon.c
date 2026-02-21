#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// THEMES I AM USING AT THE MOMENT

const char *nvim_ashen = "return {\n"
                         "  {\n"
                         "    \"ficcdaf/ashen.nvim\",\n"
                         "    lazy = false,\n"
                         "    priority = 1000,\n"
                         "    opts = {\n"
                         "      style = {\n"
                         "        bold = false,\n"
                         "        italic = false,\n"
                         "      },\n"
                         "      transparent = true,\n"
                         "    },\n"
                         "    config = function(_, opts)\n"
                         "      require(\"ashen\").setup(opts)\n"
                         "      vim.cmd.colorscheme(\"ashen\")\n"
                         "    end,\n"
                         "  },\n"
                         "}\n";

const char *nvim_rose = "return {\n"
                        "  \"rose-pine/neovim\",\n"
                        "  name = \"rose-pine\",\n"
                        "  config = function()\n"
                        "    require(\"rose-pine\").setup({\n"
                        "      variant = \"main\",\n"
                        "      styles = {\n"
                        "        transparency = true,\n"
                        "      },\n"
                        "    })\n"
                        "    vim.cmd.colorscheme(\"rose-pine\")\n"
                        "  end,\n"
                        "}\n";

const char *alac_vesper =
    "[general]\n"
    "import = [\"~/.config/alacritty/themes/vesper.toml\"]\n"
    "[font]\n"
    "normal = { family = \"JetBrainsMono Nerd Font\", style = \"Regular\" }\n"
    "size = 16\n"
    "[window]\n"
    "opacity = 0.85\n"
    "dynamic_title = true\n";

const char *alac_rose =
    "[general]\n"
    "import = [\"~/.config/alacritty/themes/rose-pine.toml\"]\n"
    "[font]\n"
    "normal = { family = \"JetBrainsMono Nerd Font\", style = \"Regular\" }\n"
    "size = 16\n"
    "[window]\n"
    "opacity = 0.85\n"
    "dynamic_title = true\n";

void write_theme(const char *filepath, const char *content) {
  FILE *fp = fopen(filepath, "w");
  if (fp == NULL) {
    fprintf(stderr, "Cannot open target file %s\n", filepath);
    exit(1);
  }
  fputs(content, fp);
  fclose(fp);
}

int main(void) {
  time_t now = time(NULL);
  struct tm *now_tm = localtime(&now);
  int hour = now_tm->tm_hour;
  int min = now_tm->tm_min;

  bool is_daytime = false;
  if ((hour > 6 || (hour == 6 && min >= 0)) &&
      (hour < 17 || (hour == 17 && min < 30))) {
    is_daytime = true;
  }

  const char *home = getenv("HOME");
  if (home == NULL) {
    fprintf(stderr, "Cannot find HOME environment variable\n");
    return 1;
  }

  char nvim_path[256];
  char alac_path[256];

  snprintf(nvim_path, sizeof(nvim_path),
           "%s/.config/nvim/lua/plugins/colorscheme.lua", home);
  snprintf(alac_path, sizeof(alac_path), "%s/.config/alacritty/alacritty.toml",
           home);

  if (is_daytime) {
    write_theme(nvim_path, nvim_rose);
    write_theme(alac_path, alac_rose);
    printf("Theme set to Rose Pine.\n");
  } else {
    write_theme(nvim_path, nvim_ashen);
    write_theme(alac_path, alac_vesper);
    printf("Theme set to Ashen/Vesper.\n");
  }

  return 0;
}
