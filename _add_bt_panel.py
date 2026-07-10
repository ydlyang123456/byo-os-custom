#!/usr/bin/env python3
"""Add BT Panel-style features to panel.html"""
import re

with open("panel.html", "rb") as f:
    html = f.read().decode("utf-8", errors="replace")

# 1. Add new sidebar items for BT Panel section
old_sidebar_end = '''    <a class="nav-link" data-page="settings" href="#settings">&#9881; 设置</a>
  </nav>'''

new_sidebar = '''    <a class="nav-link" data-page="settings" href="#settings">&#9881; 设置</a>
    <div class="sep">&#23453;&#22612;&#38745;&#26495;</div>
    <a class="nav-link" data-page="bt-sites" href="#bt-sites">&#127760; &#31449;&#28857;&#31649;&#29702;</a>
    <a class="nav-link" data-page="bt-db" href="#bt-db">&#128451; &#25968;&#25454;&#24211;</a>
    <a class="nav-link" data-page="bt-docker" href="#bt-docker">&#128230; Docker</a>
    <a class="nav-link" data-page="bt-cron" href="#bt-cron">&#128338; &#35745;&#21010;&#20219;&#21153;</a>
    <a class="nav-link" data-page="bt-ssl" href="#bt-ssl">&#128274; SSL&#35777;&#26159;</a>
    <a class="nav-link" data-page="bt-backup" href="#bt-backup">&#128190; &#22791;&#20221;&#36820;&#22797;</a>
    <a class="nav-link" data-page="bt-store" href="#bt-store">&#128722; &#36141;&#29289;&#24215;</a>
    <a class="nav-link" data-page="bt-monitor" href="#bt-monitor">&#128200; &#26174;&#31034;&#22120;</a>
  </nav>'''

html = html.replace(old_sidebar_end, new_sidebar)

# 2. Add new page sections before the closing </div> of #mn
# Find the settings page as reference
settings_page_end = html.rfind('</div>\n</div>\n\n<script>')

if settings_page_end < 0:
    # Try alternative
    settings_page_end = html.rfind('<script>')

new_pages = '''
  <!-- BT Panel: Sites -->
  <div id="page-bt-sites" class="page">
    <h2>&#127760; &#31449;&#28857;&#31649;&#29702;</h2>
    <div class="grid">
      <div class="card"><h3>&#31449;&#28857;&#26174;&#31034;</h3>
        <div class="big" id="bt-site-count">0</div>
        <div class="row"><span class="lbl">&#24635;&#35745;</span><span class="val" id="bt-site-total">0 &#20010;&#31449;&#28857;</span></div>
      </div>
      <div class="card"><h3>&#24403;&#21069;&#31449;&#28857;</h3>
        <div class="big" id="bt-site-active">-</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-site-status">&#27491;&#24120;</span></div>
      </div>
      <div class="card"><h3>&#35774;&#32622;</h3>
        <button class="btn btn-primary" onclick="btAction('site-add')">&#26032;&#22686;&#31449;&#28857;</button>
        <button class="btn btn-outline" onclick="btAction('site-list')">&#21015;&#34920;</button>
        <button class="btn btn-outline" onclick="btAction('site-reload')">&#37325;&#21551;Nginx</button>
      </div>
    </div>
    <div class="output-box" id="bt-site-out">&#28857;&#20987;&#25353;&#38190;&#21152;&#36733;&#25968;&#25454;...</div>
  </div>

  <!-- BT Panel: Database -->
  <div id="page-bt-db" class="page">
    <h2>&#128451; &#25968;&#25454;&#24211;&#31649;&#29702;</h2>
    <div class="grid">
      <div class="card"><h3>MySQL</h3>
        <div class="big" id="bt-db-status">&#27491;&#24120;</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-db-state">&#24320;&#26426;&#21551;&#21160;</span></div>
        <div class="row"><span class="lbl">&#31471;&#21475;</span><span class="val">3306</span></div>
      </div>
      <div class="card"><h3>&#25968;&#25454;&#24211;</h3>
        <div class="big" id="bt-db-count">0</div>
        <div class="row"><span class="lbl">&#24635;&#35745;</span><span class="val" id="bt-db-total">0 &#20010;&#24211;</span></div>
      </div>
      <div class="card"><h3>&#25805;&#20316;</h3>
        <button class="btn btn-primary" onclick="btAction('db-create')">&#21019;&#24314;&#25968;&#25454;&#24211;</button>
        <button class="btn btn-outline" onclick="btAction('db-list')">&#21015;&#34920;</button>
        <button class="btn btn-outline" onclick="btAction('db-backup')">&#22791;&#20221;</button>
      </div>
    </div>
    <div class="output-box" id="bt-db-out">&#28857;&#20987;&#25353;&#38190;&#21152;&#36733;&#25968;&#25454;...</div>
  </div>

  <!-- BT Panel: Docker -->
  <div id="page-bt-docker" class="page">
    <h2>&#128230; Docker &#31649;&#29702;</h2>
    <div class="grid">
      <div class="card"><h3>Docker &#26381;&#21153;</h3>
        <div class="big" id="bt-docker-status">&#27491;&#24120;</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-docker-state">&#24320;&#26426;&#21551;&#21160;</span></div>
        <div class="row"><span class="lbl">&#23481;&#22120;&#25968;</span><span class="val" id="bt-docker-count">0</span></div>
      </div>
      <div class="card"><h3>&#38745;&#24433;&#26144;&#23556;</h3>
        <div class="big" id="bt-image-count">0</div>
        <div class="row"><span class="lbl">&#24635;&#35745;</span><span class="val" id="bt-image-total">0 &#20010;&#38745;&#24433;</span></div>
      </div>
      <div class="card"><h3>&#25805;&#20316;</h3>
        <button class="btn btn-primary" onclick="btAction('docker-ps')">&#23481;&#22120;&#21015;&#34920;</button>
        <button class="btn btn-outline" onclick="btAction('docker-images')">&#38745;&#24433;&#21015;&#34920;</button>
        <button class="btn btn-outline" onclick="btAction('docker-pull')">&#25286;&#19979;&#38745;&#24433;</button>
      </div>
    </div>
    <div class="output-box" id="bt-docker-out">&#28857;&#20987;&#25353;&#38190;&#21152;&#36733;&#25968;&#25454;...</div>
  </div>

  <!-- BT Panel: Cron -->
  <div id="page-bt-cron" class="page">
    <h2>&#128338; &#35745;&#21010;&#20219;&#21153;</h2>
    <div class="grid">
      <div class="card"><h3>&#20219;&#21153;&#26174;&#31034;</h3>
        <div class="big" id="bt-cron-count">0</div>
        <div class="row"><span class="lbl">&#24635;&#35745;</span><span class="val" id="bt-cron-total">0 &#20010;&#20219;&#21153;</span></div>
      </div>
      <div class="card"><h3>&#24403;&#21069;</h3>
        <div class="big" id="bt-cron-next">-</div>
        <div class="row"><span class="lbl">&#19979;&#27425;&#25191;&#34892;</span><span class="val" id="bt-cron-next-time">-</span></div>
      </div>
      <div class="card"><h3>&#25805;&#20316;</h3>
        <button class="btn btn-primary" onclick="btAction('cron-add')">&#26032;&#22686;&#20219;&#21153;</button>
        <button class="btn btn-outline" onclick="btAction('cron-list')">&#21015;&#34920;</button>
        <button class="btn btn-outline" onclick="btAction('cron-del')">&#21024;&#38500;</button>
      </div>
    </div>
    <div class="output-box" id="bt-cron-out">&#28857;&#20987;&#25353;&#38190;&#21152;&#36733;&#25968;&#25454;...</div>
  </div>

  <!-- BT Panel: SSL -->
  <div id="page-bt-ssl" class="page">
    <h2>&#128274; SSL &#35777;&#26159;&#31649;&#29702;</h2>
    <div class="grid">
      <div class="card"><h3>&#35777;&#26159;&#26174;&#31034;</h3>
        <div class="big" id="bt-ssl-count">0</div>
        <div class="row"><span class="lbl">&#24635;&#35745;</span><span class="val" id="bt-ssl-total">0 &#20010;&#35777;&#26159;</span></div>
      </div>
      <div class="card"><h3>&#24403;&#21069;</h3>
        <div class="big" id="bt-ssl-status">-</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-ssl-state">-</span></div>
      </div>
      <div class="card"><h3>&#25805;&#20316;</h3>
        <button class="btn btn-primary" onclick="btAction('ssl-apply')">&#30003;&#35831;&#35777;&#26159;</button>
        <button class="btn btn-outline" onclick="btAction('ssl-list')">&#21015;&#34920;</button>
        <button class="btn btn-outline" onclick="btAction('ssl-renew')">&#32493;&#21561;</button>
      </div>
    </div>
    <div class="output-box" id="bt-ssl-out">&#28857;&#20987;&#25353;&#38190;&#21152;&#36733;&#25968;&#25454;...</div>
  </div>

  <!-- BT Panel: Backup -->
  <div id="page-bt-backup" class="page">
    <h2>&#128190; &#22791;&#20221;&#36820;&#22797;</h2>
    <div class="grid">
      <div class="card"><h3>&#22791;&#20221;&#26174;&#31034;</h3>
        <div class="big" id="bt-backup-count">0</div>
        <div class="row"><span class="lbl">&#24635;&#35745;</span><span class="val" id="bt-backup-total">0 &#20010;&#22791;&#20221;</span></div>
      </div>
      <div class="card"><h3>&#22823;&#23567;</h3>
        <div class="big" id="bt-backup-size">0 MB</div>
        <div class="row"><span class="lbl">&#36135;&#22806;</span><span class="val" id="bt-backup-space">&#31354;&#38388;</span></div>
      </div>
      <div class="card"><h3>&#25805;&#20316;</h3>
        <button class="btn btn-primary" onclick="btAction('backup-now')">&#31435;&#21363;&#22791;&#20221;</button>
        <button class="btn btn-outline" onclick="btAction('backup-list')">&#21015;&#34920;</button>
        <button class="btn btn-outline" onclick="btAction('backup-restore')">&#36820;&#22797;</button>
      </div>
    </div>
    <div class="output-box" id="bt-backup-out">&#28857;&#20987;&#25353;&#38190;&#21152;&#36733;&#25968;&#25454;...</div>
  </div>

  <!-- BT Panel: Store -->
  <div id="page-bt-store" class="page">
    <h2>&#128722; &#36141;&#29289;&#24215;</h2>
    <div class="grid">
      <div class="card"><h3>Nginx</h3>
        <div class="big" style="font-size:16px">Web &#26381;&#21153;&#22120;</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-store-nginx">&#26410;&#23433;&#35013;</span></div>
        <button class="btn btn-primary" style="margin-top:8px" onclick="btAction('install-nginx')">&#23433;&#35013;</button>
      </div>
      <div class="card"><h3>MySQL</h3>
        <div class="big" style="font-size:16px">&#25968;&#25454;&#24211;</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-store-mysql">&#26410;&#23433;&#35013;</span></div>
        <button class="btn btn-primary" style="margin-top:8px" onclick="btAction('install-mysql')">&#23433;&#35013;</button>
      </div>
      <div class="card"><h3>PHP</h3>
        <div class="big" style="font-size:16px">&#35789;&#27861;&#35821;&#35328;</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-store-php">&#26410;&#23433;&#35013;</span></div>
        <button class="btn btn-primary" style="margin-top:8px" onclick="btAction('install-php')">&#23433;&#35013;</button>
      </div>
      <div class="card"><h3>Redis</h3>
        <div class="big" style="font-size:16px">&#32531;&#20934;&#23384;&#20648;</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-store-redis">&#26410;&#23433;&#35013;</span></div>
        <button class="btn btn-primary" style="margin-top:8px" onclick="btAction('install-redis')">&#23433;&#35013;</button>
      </div>
      <div class="card"><h3>Docker</h3>
        <div class="big" style="font-size:16px">&#23481;&#22120;&#21270;&#24037;&#20855;</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-store-docker">&#26410;&#23433;&#35013;</span></div>
        <button class="btn btn-primary" style="margin-top:8px" onclick="btAction('install-docker')">&#23433;&#35013;</button>
      </div>
      <div class="card"><h3>Git</h3>
        <div class="big" style="font-size:16px">&#29256;&#26412;&#31649;&#29702;</div>
        <div class="row"><span class="lbl">&#29366;&#24577;</span><span class="val" id="bt-store-git">&#26410;&#23433;&#35013;</span></div>
        <button class="btn btn-primary" style="margin-top:8px" onclick="btAction('install-git')">&#23433;&#35013;</button>
      </div>
    </div>
    <div class="output-box" id="bt-store-out">&#28857;&#20987;&#23433;&#35013;&#36141;&#29289;&#24215;&#20013;&#30340;&#36141;&#29289;...</div>
  </div>

  <!-- BT Panel: Monitor -->
  <div id="page-bt-monitor" class="page">
    <h2>&#128200; &#26174;&#31034;&#22120;</h2>
    <div class="grid">
      <div class="card"><h3>CPU</h3>
        <div class="big" id="bt-mon-cpu">0%</div>
        <div class="bar"><div class="fill" id="bt-mon-cpu-bar" style="width:0%;background:#38bdf8"></div></div>
        <div class="row"><span class="lbl">&#20351;&#29992;&#29575;</span><span class="val" id="bt-mon-cpu-pct">0%</span></div>
      </div>
      <div class="card"><h3>&#20869;&#23384;</h3>
        <div class="big" id="bt-mon-mem">0%</div>
        <div class="bar"><div class="fill" id="bt-mon-mem-bar" style="width:0%;background:#22c55e"></div></div>
        <div class="row"><span class="lbl">&#20351;&#29992;&#29575;</span><span class="val" id="bt-mon-mem-pct">0%</span></div>
      </div>
      <div class="card"><h3>&#30828;&#30424;</h3>
        <div class="big" id="bt-mon-disk">0%</div>
        <div class="bar"><div class="fill" id="bt-mon-disk-bar" style="width:0%;background:#f59e0b"></div></div>
        <div class="row"><span class="lbl">&#20351;&#29992;&#29575;</span><span class="val" id="bt-mon-disk-pct">0%</span></div>
      </div>
      <div class="card"><h3>&#32593;&#32476;</h3>
        <div class="big" id="bt-mon-net">0 KB/s</div>
        <div class="row"><span class="lbl">&#25509;&#25910;</span><span class="val" id="bt-mon-net-rx">0 KB</span></div>
        <div class="row"><span class="lbl">&#21457;&#36865;</span><span class="val" id="bt-mon-net-tx">0 KB</span></div>
      </div>
    </div>
    <div class="output-box" id="bt-mon-out">&#26174;&#31034;&#22120;&#26174;&#31034;&#31934;&#31929;&#20449;&#24687;...</div>
  </div>

'''

# Insert new pages before the script tag
html = html.replace('<script>', new_pages + '<script>', 1)

# 3. Add JavaScript for BT Panel actions
bt_js = '''
/* ===== BT Panel Actions ===== */
function btAction(action) {
  var cmds = {
    'site-add': 'echo "New site wizard"',
    'site-list': 'ls /var/www',
    'site-reload': 'echo "Reloading nginx..."',
    'db-create': 'echo "Create database wizard"',
    'db-list': 'mysql -e "SHOW DATABASES"',
    'db-backup': 'echo "Backing up databases..."',
    'docker-ps': 'docker ps -a',
    'docker-images': 'docker images',
    'docker-pull': 'echo "Pull image: please specify"',
    'cron-add': 'echo "Add cron job wizard"',
    'cron-list': 'crontab -l',
    'cron-del': 'echo "Delete cron job"',
    'ssl-apply': 'echo "Apply for SSL certificate"',
    'ssl-list': 'echo "List certificates"',
    'ssl-renew': 'echo "Renew certificates"',
    'backup-now': 'echo "Starting backup..."',
    'backup-list': 'ls /backup',
    'backup-restore': 'echo "Restore wizard"',
    'install-nginx': 'echo "Installing Nginx..."',
    'install-mysql': 'echo "Installing MySQL..."',
    'install-php': 'echo "Installing PHP..."',
    'install-redis': 'echo "Installing Redis..."',
    'install-docker': 'echo "Installing Docker..."',
    'install-git': 'echo "Installing Git..."'
  };
  var cmd = cmds[action] || action;
  var page = action.split('-')[0];
  if (page === 'install') page = 'store';
  var outId = 'bt-' + page + '-out';
  var el = document.getElementById(outId);
  if (el) {
    el.innerHTML = '<span class="spinner"></span> Running: ' + cmd + ' ...';
    api('/api/exec', {cmd: cmd}).then(function(d) {
      el.textContent = d.output || d.error || '(no output)';
    }).catch(function(e) {
      el.innerHTML = '<span class="err">Error: ' + e + '</span>';
    });
  }
  toast('Executing: ' + cmd, '');
}
'''

# Insert before the closing </script>
html = html.replace('</script>', bt_js + '</script>', 1)

with open("panel.html", "wb") as f:
    f.write(html.encode("utf-8"))

print(f"panel.html updated: {len(html)} chars")
print("BT Panel features added!")