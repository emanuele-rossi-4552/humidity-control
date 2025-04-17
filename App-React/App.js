import React, { useEffect, useState } from "react";
import { initializeApp } from "firebase/app";
import { getFirestore, collection, getDocs } from "firebase/firestore";
import dayjs from "dayjs";
import {
  LineChart, Line, XAxis, YAxis, Tooltip, Legend, CartesianGrid, ResponsiveContainer
} from "recharts";

// Firebase configuration (you can find these details in your Firebase project settings)
const firebaseConfig = {
  apiKey: "API_key",
  authDomain: "Domain",
  projectId: "Project_ID",
  storageBucket: "Storage",
  messagingSenderId: "Sende_ID",
  appId: "App_ID"
};

// Initialize Firebase app with the given configuration
const app = initializeApp(firebaseConfig);

// Create a reference to the Firestore database
const db = getFirestore(app);

function App() {
  // State to store the data fetched from Firestore
  const [dati, setDati] = useState([]);

  // States to filter data by year, month and day
  const [anno, setAnno] = useState(dayjs().year());
  const [mese, setMese] = useState(dayjs().month() + 1);
  const [giorno, setGiorno] = useState(dayjs().date());

  // React hook to fetch data once when the component mounts
  useEffect(() => {
    const leggiDati = async () => {
      try {
        // Fetch all documents from the "letture" collection in Firestore
        const querySnapshot = await getDocs(collection(db, "letture"));
        const lista = [];

        // Process each document and store relevant fields
        querySnapshot.forEach((doc) => {
          const dati = doc.data();
          lista.push({
            data: dati.Data_lettura || "N/A",
            umidita: dati.Umidita || "N/A",
            temperatura: dati.Temperatura || "N/A"
          });
        });

        console.log("Documents retrieved:", lista);
        setDati(lista);
      } catch (e) {
        console.error("Error fetching data:", e);
      }
    };

    leggiDati();
  }, []); // Empty dependency array to run only on mount

  // Filter data for the entire year
  const datiPerAnno = dati.filter(d => dayjs(d.data).year() === parseInt(anno));
  // Filter data for the selected month
  const datiPerMese = dati.filter(d =>
    dayjs(d.data).year() === parseInt(anno) &&
    dayjs(d.data).month() + 1 === parseInt(mese)
  );
  // Filter data for the selected day
  const datiPerGiorno = dati.filter(d =>
    dayjs(d.data).year() === parseInt(anno) &&
    dayjs(d.data).month() + 1 === parseInt(mese) &&
    dayjs(d.data).date() === parseInt(giorno)
  );

  // Reusable chart component for humidity or temperature
  const Grafico = ({ dati, tipo }) => (
    <ResponsiveContainer width="100%" height={300}>
      <LineChart data={dati.sort((a, b) => new Date(a.data) - new Date(b.data))}>
        <CartesianGrid stroke="#ccc" />
        <XAxis dataKey="data" tick={{ fontSize: 10 }} />
        <YAxis />
        <Tooltip />
        <Legend />
        <Line
          type="monotone"
          dataKey={tipo}
          stroke={tipo === "umidita" ? "#3498db" : "#e67e22"}
        />
      </LineChart>
    </ResponsiveContainer>
  );

  return (
    <div style={{ padding: "20px", textAlign: "center" }}>
      <h1 style={{ color: "#3498db" }}>Home Humidity Tracker</h1>

      <div>
        <label>
          Year:
          <input
            type="number"
            value={anno}
            onChange={(e) => setAnno(e.target.value)}
            style={{ margin: "5px" }}
          />
        </label>
        <label>
          Month:
          <input
            type="number"
            min="1"
            max="12"
            value={mese}
            onChange={(e) => setMese(e.target.value)}
            style={{ margin: "5px" }}
          />
        </label>
        <label>
          Day:
          <input
            type="number"
            min="1"
            max="31"
            value={giorno}
            onChange={(e) => setGiorno(e.target.value)}
            style={{ margin: "5px" }}
          />
        </label>
      </div>

      <h3>Year Overview</h3>
      <div style={{ display: "flex", gap: "10px" }}>
        <div style={{ width: "50%" }}><Grafico dati={datiPerAnno} tipo="umidita" /></div>
        <div style={{ width: "50%" }}><Grafico dati={datiPerAnno} tipo="temperatura" /></div>
      </div>

      <h3>Month Overview</h3>
      <div style={{ display: "flex", gap: "10px" }}>
        <div style={{ width: "50%" }}><Grafico dati={datiPerMese} tipo="umidita" /></div>
        <div style={{ width: "50%" }}><Grafico dati={datiPerMese} tipo="temperatura" /></div>
      </div>

      <h3>Day Overview</h3>
      <div style={{ display: "flex", gap: "10px" }}>
        <div style={{ width: "50%" }}><Grafico dati={datiPerGiorno} tipo="umidita" /></div>
        <div style={{ width: "50%" }}><Grafico dati={datiPerGiorno} tipo="temperatura" /></div>
      </div>
    </div>
  );
}

export default App;
