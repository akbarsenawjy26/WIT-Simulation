from flask import Flask, jsonify
from influxdb_client import InfluxDBClient

app = Flask(__name__)

influxdb_url = "http://localhost:8086"
influxdb_token = "6ZhdRSn7TKnmik7V13ha7i-nkBz22geD_PXvAzQV_RgYTBpgGcYLB2hGwNzpvh5LiRoSmTQD8KCGCutkDjjxSw=="
influxdb_org = "WIT.SBY"
influxdb_bucket = "bucket@wit"

client = InfluxDBClient(url=influxdb_url, token=influxdb_token, org=influxdb_org)

def query_data(measurement):
    try:
        query_api = client.query_api()
        query = f'from(bucket:"{influxdb_bucket}") |> range(start: -15m) |> filter(fn: (r) => r["_measurement"] == "{measurement}") |> filter(fn: (r) => r["_field"] == "value")'
        result = query_api.query(query=query)
        data = []
        for table in result:
            for row in table.records:
                data.append({
                    "_field": row.get_field(),
                    "_measurement": row.get_measurement(),
                    "_value": row.get_value(),
                    "_time": row.get_time()
                })
        return data
    except Exception as e:
        return {"error": str(e)}

@app.route('/api/temperature', methods=['GET'])
def get_temperature():
    data = query_data("wit/simulasi/temperature")
    return jsonify(data)

@app.route('/api/rpm', methods=['GET'])
def get_rpm():
    data = query_data("wit/simulasi/RPM")
    return jsonify(data)

@app.route('/api/heartbeat', methods=['GET'])
def get_heartbeat():
    data = query_data("wit/simulasi/heartbeat")
    return jsonify(data)

if __name__ == '__main__':
    app.run(debug=True)
