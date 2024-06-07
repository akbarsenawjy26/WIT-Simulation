const express = require("express");
const { dataStore } = require("./mqttClient"); // Impor dataStore dari mqttClient

const app = express();
const port = 3001;
const router = express.Router();

// Endpoint API untuk menampilkan data
router.get("/api/data", (req, res) => {
  console.log("datastore:", dataStore);
  res.json({
    topic1: dataStore.topic1,
    topic2: dataStore.topic2,
    topic3: dataStore.topic3,
  });
});

app.use(router);

app.listen(port, () => {
  console.log(`Server berjalan di http://localhost:${port}`);
});
