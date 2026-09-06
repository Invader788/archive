(menu-bar-mode -1)
(tool-bar-mode -1)
(scroll-bar-mode -1)
(setq inhibit-startup-screen t)

(use-package modus-themes
  :ensure t
  :config
  (setq modus-themes-mode-line '(accented borderless)
        modus-themes-region '(bg-only)
        modus-themes-org-blocks 'gray-background)
  (load-theme 'modus-vivendi t))   ; dark theme

(use-package doom-themes
  :ensure t
  :config
  (load-theme 'doom-one t)          ; or doom-dracula, doom-nord, doom-solarized-dark, etc.
  (doom-themes-visual-bell-config))
