#!/bin/sh
find src -name "*.cpp" -o -name "*.h" -o -name "*.qml" | sort > sources.list
xgettext \
  --from-code=UTF-8 \
  --c++ \
  --kde \
  --add-comments=i18n \
  --keyword=i18n:1 \
  --keyword=i18nc:1c,2 \
  --keyword=i18np:1,2 \
  --keyword=i18ncp:1c,2,3 \
  --keyword=ki18n:1 \
  --keyword=ki18nc:1c,2 \
  --keyword=ki18np:1,2 \
  --keyword=ki18ncp:1c,2,3 \
  --output=i18n/com.github.zsd2024.LuoguDesktop.pot \
  --files-from=sources.list
rm -rf sources.list
msgmerge --update --backup=none --previous i18n/zh_CN/com.github.zsd2024.LuoguDesktop.po i18n/com.github.zsd2024.LuoguDesktop.pot
