#!/bin/bash
conf="/usr/share/e-sabit/e-sabit.json"   # JSON biçiminde
# Eski yapıyla aynı mantıkta kullanıcı dizinini çek
usr=$(jq -r '.[0].kullaniciDizin' "$conf")
user=$(basename "$usr")
# yedekState true ise bilgi değişkeni 1 gibi çalışsın
yedekState=$(jq -r '.[0].yedekState' "$conf")
backup="/var/backups/e-sabit/$user"
esabit="/home/$user/Masaüstü/esabit"

# Eski sistemde: bilgi == "yedekState|1"
# Yeni sistemde: yedekState == true
if [ "$yedekState" == "true" ]; then

        # Eğer Serbest dizini yoksa oluştur
        if [ ! -d "$esabit" ]; then
            mkdir -p "$esabit"
            chown "$user":"$user" "$esabit"
            chmod 755 "$esabit"
        fi

        if [ -d "$backup" ]; then
                rsync -apoglr --delete \
                    --exclude='Masaüstü/esabit' \
                    "$backup"/ /home/"$user"/

                chown -R "$user":"$user" /home/"$user"/
                chmod -R 755 /home/"$user"/   # gerekmedikçe devre dışı bırak
        fi
fi
