# hyprland configuration

{inputs, pkgs, ...}: {
  programs.hyprland = {
    enable = true;
    # set the flake package
    package = inputs.hyprland.packages.${pkgs.stdenv.hostPlatform.system}.hyprland;
    # make sure to also set the portal package, so that they are in sync
    portalPackage = inputs.hyprland.packages.${pkgs.stdenv.hostPlatform.system}.xdg-desktop-portal-hyprland;
  };

  # Optional, hint Electron apps to use Wayland:
  home.sessionVariables.NIXOS_OZONE_WL = "1";

  wayland.windowManager.hyprland = {
    enable = true;
    #enableNvidiaPatches = true;
    extraConfig =  ''
    $mod = SUPER

    env = LIBVA_DRIVER_NAME,nvidia
    env = XDG_SESSION_TYPE,wayland
    env = NVD_BACKEND,direct
    #env = GBM_BACKEND,nvidia-drm
    env = __GLX_VENDOR_LIBRARY_NAME,nvidia
    #env = WLR_NO_HARDWARE_CURSORS,1
    #env = XCURSOR_SIZE, 24
    
    #exec-once = swaybg -i /home/aki/walls/chinese-hills.jpg
    #exec-once = waybar

    # For all categories, see https://wiki.hyprland.org/Configuring/Variables/
    input {
      kb_layout = us
      kb_variant =
      kb_model =
      kb_options =
      kb_rules =

      follow_mouse = 1

      touchpad {
        natural_scroll = false
      }

      sensitivity = 0 # -1.0 - 1.0, 0 means no modification.
    }

    general {
      gaps_in = 10
      gaps_out = 10
      border_size = 3
      col.active_border = rgba(88888888)
      col.inactive_border = rgba(00000088)

      layout = master
     }
 
    decoration {
      rounding = 5
      blur {
        enabled = true
        size = 10
        passes = 3
        new_optimizations = true
        brightness = 1.0
        contrast = 1.0
        noise = 0.02
      }

      drop_shadow = true
      shadow_ignore_window = true
      shadow_offset = 0 2
      shadow_range = 20
      shadow_render_power = 3
      col.shadow = rgba(00000055)
    }

    animations {
      enabled = true
      animation = border, 1, 2, default
      animation = fade, 1, 4, default
      animation = windows, 1, 3, default, popin 80%
      animation = workspaces, 1, 2, default, slide
    }

    dwindle {
      # keep floating dimentions while tiling
      pseudotile = true
      preserve_split = true
    }

    master {
    # See https://wiki.hyprland.org/Configuring/Master-Layout/ for more
      new_is_master = true
    }


    gestures {
    # See https://wiki.hyprland.org/Configuring/Variables/ for more
     workspace_swipe = false
    }

    # make Firefox PiP window floating and sticky
    windowrulev2 = float, title:^(Picture-in-Picture)$
    windowrulev2 = pin, title:^(Picture-in-Picture)$

    # throw sharing indicators away
    windowrulev2 = workspace special silent, title:^(Firefox — Sharing Indicator)$
    windowrulev2 = workspace special silent, title:^(.*is sharing (your screen|a window)\.)$


    # start Discord/WebCord in ws2
    windowrulev2 = workspace 2, title:^(.*(Disc|WebC)ord.*)$

    # idle inhibit while watching videos
    windowrulev2 = idleinhibit focus, class:^(mpv|.+exe)$
    windowrulev2 = idleinhibit focus, class:^(firefox)$, title:^(.*YouTube.*)$
    windowrulev2 = idleinhibit fullscreen, class:^(firefox)$

    windowrulev2 = dimaround, class:^(gcr-prompter)$

    # fix xwayland apps
    # windowrulev2 = rounding 0, xwayland:1, floating:1
    # windowrulev2 = center, class:^(.*jetbrains.*)$, title:^(Confirm Exit|Open Project|win424|win201|splash)$
    # windowrulev2 = size 640 400, class:^(.*jetbrains.*)$, title:^(splash)$


    # mouse movements
    bindm = $mod, mouse:272, movewindow
    bindm = $mod, mouse:273, resizewindow

    # commands
    bind = $mod Shift, Q, exec, pkill Hyprland
    bind = $mod, Q, killactive,
    bind = $mod, F, fullscreen,
    bind = $mod, W, togglesplit,
    bind = $mod, S, togglefloating,
    bind = $mod, P, pseudo,

    # utility
    # launcher
    bind = $mod, D, exec, wofi --show drun
    # terminal
    bind = $mod, Return, exec, alacritty
    bind = $mod Shift, Return, exec, ghostty
  
    # move focus
    bind = $mod, left, movefocus, l
    bind = $mod, right, movefocus, r
    bind = $mod, up, movefocus, u
    bind = $mod, down, movefocus, d

  # Switch workspaces with mainMod + [0-9]
  bind = $mod, 1, workspace, 1
  bind = $mod, 2, workspace, 2
  bind = $mod, 3, workspace, 3
  bind = $mod, 4, workspace, 4
  bind = $mod, 5, workspace, 5
  bind = $mod, 6, workspace, 6
  bind = $mod, 7, workspace, 7
  bind = $mod, 8, workspace, 8
  bind = $mod, 9, workspace, 9

  # Move active window to a workspace with mainMod + SHIFT + [0-9]
  bind = $mod SHIFT, 1, movetoworkspace, 1
  bind = $mod SHIFT, 2, movetoworkspace, 2
  bind = $mod SHIFT, 3, movetoworkspace, 3
  bind = $mod SHIFT, 4, movetoworkspace, 4
  bind = $mod SHIFT, 5, movetoworkspace, 5
  bind = $mod SHIFT, 6, movetoworkspace, 6
  bind = $mod SHIFT, 7, movetoworkspace, 7
  bind = $mod SHIFT, 8, movetoworkspace, 8
  bind = $mod SHIFT, 9, movetoworkspace, 9


  # volume
  bindle = , XF86AudioRaiseVolume, exec, wpctl set-volume -l "1.0" @DEFAULT_AUDIO_SINK@ 6%+
  bindle = , XF86AudioLowerVolume, exec, wpctl set-volume -l "1.0" @DEFAULT_AUDIO_SINK@ 6%-
  bindl = , XF86AudioMute, exec, wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle
  bindl = , XF86AudioMicMute, exec, wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle

  # backlight
  binde = , XF86MonBrightnessUp, exec, brightnessctl set 10%+
  binde = , XF86MonBrightnessDown, exec, brightnessctl set 10%-

  # screenshot
  # stop animations while screenshotting; makes black border go away

  bind = CTRL, Print, exec, grimblast --notify --cursor copysave output
  bind = $mod SHIFT CTRL, R, exec, grimblast --notify --cursor copysave output

  bind = ALT, Print, exec, grimblast --notify --cursor copysave screen
  bind = $mod SHIFT ALT, R, exec, grimblast --notify --cursor copysave screen

  '';
  };

  
}
