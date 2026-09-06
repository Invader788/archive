# =============================================
# Solid Slate Grey qutebrowser config.py
# No Transparency - Clean & Minimal
# =============================================

config.load_autoconfig(False)

# === Core Window Settings ===
c.window.transparent = False

# Webpage colors
c.colors.webpage.bg = '#121212'
c.colors.webpage.darkmode.enabled = True
c.colors.webpage.darkmode.policy.images = 'always'
c.colors.webpage.preferred_color_scheme = 'dark'

# === UI Elements - Solid Grey ===

# The Container (The space behind the tabs)
c.colors.tabs.bar.bg = '#1e1e1e'

# Tabs - Unselected (Dark Grey)
c.colors.tabs.even.bg = '#2a2a2a'
c.colors.tabs.odd.bg  = '#252525'
c.colors.tabs.even.fg = '#a0a0a0'
c.colors.tabs.odd.fg  = '#a0a0a0'

# Tabs - Selected (Lighter Grey)
c.colors.tabs.selected.even.bg = '#3d3d3d'
c.colors.tabs.selected.odd.bg  = '#3d3d3d'
c.colors.tabs.selected.even.fg = '#ffffff'
c.colors.tabs.selected.odd.fg  = '#ffffff'

# Tabs - Pinned
c.colors.tabs.pinned.even.bg = '#2a2a2a'
c.colors.tabs.pinned.odd.bg  = '#252525'
c.colors.tabs.pinned.even.fg = '#d0d0d0'
c.colors.tabs.pinned.odd.fg  = '#d0d0d0'

# Indicator (Silver/White line for active tab)
c.colors.tabs.indicator.start = '#888888'
c.colors.tabs.indicator.stop = '#ffffff'
c.tabs.indicator.width = 3

# === Statusbar ===
c.colors.statusbar.normal.bg = '#1e1e1e'
c.colors.statusbar.normal.fg = '#d0d0d0'
c.colors.statusbar.insert.bg = '#3d3d3d'
c.colors.statusbar.insert.fg = '#ffffff'
c.colors.statusbar.command.bg = '#1e1e1e'
c.colors.statusbar.url.fg = '#d0d0d0'
c.colors.statusbar.url.hover.fg = '#ffffff'
c.colors.statusbar.url.success.https.fg = '#ffffff'

# Completion
c.colors.completion.fg = '#eeeeee'
c.colors.completion.odd.bg = '#252525'
c.colors.completion.even.bg = '#2a2a2a'
c.colors.completion.category.bg = '#1e1e1e'
c.colors.completion.item.selected.bg = '#444444'
c.colors.completion.item.selected.fg = '#ffffff'
c.colors.completion.item.selected.border.top = '#444444'
c.colors.completion.item.selected.border.bottom = '#444444'

# Hints (High Contrast Slate)
c.colors.hints.bg = '#3d3d3d'
c.colors.hints.fg = '#ffffff'
c.colors.hints.match.fg = '#888888'
c.hints.radius = 4

# === Layout & Behavior ===
c.tabs.position = 'top'
c.tabs.padding = {'top': 8, 'bottom': 8, 'left': 10, 'right': 10}
c.statusbar.padding = {'top': 5, 'bottom': 5, 'left': 8, 'right': 8}

c.url.start_pages = ["https://start.duckduckgo.com"]
c.url.default_page = "https://start.duckduckgo.com"

c.scrolling.smooth = True
c.content.javascript.enabled = True

# === Keybinds ===
config.bind(',d', 'config-cycle colors.webpage.darkmode.enabled true false')
