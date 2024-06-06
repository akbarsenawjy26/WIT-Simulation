## Dokumentasi Simulasi

### Docker

1. Buka file `docker-compose.yaml`.
2. Jalankan perintah `docker-compose up -d`.
3. Periksa pada port localhost:
   a. **InfluxDB** - [localhost:8086](http://localhost:8086) - Username: akbar@wit.com - Password: akbarWIT2024
   b. **EMQX** - [localhost:18083](http://localhost:18083) - Username: admin - Password: public
   c. **MySQL** - [localhost:8081](http://localhost:8081) - Username: akbar@wit.com - Password: akbarWIT2024

### Firmware

1. Buka file firmware.
2. Kompilasi file `scr/main.cpp`.
3. Upload.
4. Persyaratan:
   a. **WiFi** - SSID: Sena - Pass: senabaik123

### Middleware

1. Buka file middleware.
2. Jalankan `middleware.py`.

### Backend

1. Buka file backend.
2. Jalankan `backend.py`.
3. End-point:
   a. [localhost:5000/api/rpm](http://localhost:5000/api/rpm)
   b. [localhost:5000/api/temperature](http://localhost:5000/api/temperature)
   c. [localhost:5000/api/heartbeat](http://localhost:5000/api/heartbeat)
