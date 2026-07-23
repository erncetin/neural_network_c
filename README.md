# Neural Network in C

Sıfırdan, herhangi bir kütüphane kullanmadan C dilinde basit bir yapay sinir ağı implementasyonu. Projenin amacı sinir ağlarının iç mekanizmasını (forward propagation, backpropagation, weight güncelleme) elle yazarak anlamaktı.

## Ne Yapıyor?

Ağ, 2 giriş nöronlu, 2 gizli katman nöronlu ve 1 çıkış nöronlu basit bir yapıya sahip. AND gate davranışını öğrenmek üzere eğitiliyor:

| Giriş 1 | Giriş 2 | Beklenen Çıkış |
|----------|----------|----------------|
| 0        | 0        | 0              |
| 0        | 1        | 0              |
| 1        | 1        | 1              |
| 1        | 0        | 0              |

Eğitim 10.000 epoch boyunca devam ediyor. Her epoch'ta training verileri shuffle edilerek ağa besleniyor. Eğitim sonunda ağ, test verilerini tahmin edip sonuçları ekrana basıyor.

## Proje Yapısı

- **`neural_network.c`** — Asıl sinir ağı kodu. Sigmoid aktivasyon, forward/backward propagation, weight initialization ve training loop'un hepsi bu dosyada.
- **`matris_multiplication.c`** — Sinir ağını yazmaya başlamadan önce matris çarpımı mantığını test etmek için yazdığım ayrı bir dosya.

## Geliştirme Süreci

Projeye adım adım ilerledim:

1. İlk olarak sigmoid ve türev fonksiyonlarını yazdım.
2. Sonra weight ve bias initialization fonksiyonlarını, shuffle fonksiyonunu ekledim.
3. Matris çarpımı ve forward propagation mantığını kurdum. Matris çarpımını ayrı bir dosyada (`matris_multiplication.c`) test ettikten sonra ana koda entegre ettim.
4. Son olarak backpropagation, training loop ve eğitim sonrası test kısmını ekleyerek ağı tamamladım.

Proje bir süre yarım kalmıştı, sonra geri dönüp `neural_network.c` dosyasını güncelleyerek backpropagation ve training loop'u ekledim ve çalışır hale getirdim.

## Derleme ve Çalıştırma

```bash
gcc neural_network.c -o neural_network -lm
./neural_network
```

`-lm` flag'i `math.h` kütüphanesini linklemek için gerekli.

## Notlar

- Aktivasyon fonksiyonu olarak sigmoid kullanılıyor.
- Learning rate 0.4 olarak ayarlanmış.
- Ağırlıklar -1 ile 1 arasında rastgele başlatılıyor, bias'lar 0'dan başlıyor.
- Her şey saf C — harici bir kütüphane veya framework yok.
