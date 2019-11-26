import axios from 'axios';
import config from '../../config';

async function getAllSettings() {
  return axios.get(`http://localhost:${config.port}/settings/debug`)
    .then(r => r.data);
}

async function getAPSettings() {
  return axios.get(`http://localhost:${config.port}/settings/ap`)
    .then(r => r.data);
}

async function setAPSettings(ssid, key) {
  return axios.post(`http://localhost:${config.port}/settings/ap`, {
    ssid: ssid,
    key: key
  })
  .then(r => r.data);
}

async function getLocationSettings() {
  return axios.get(`http://localhost:${config.port}/settings/location`)
    .then(r => r.data);
}

async function setLocationSettings(latitude, magDeclination, x_offset, y_offset, z_offset) {
  return axios.post(`http://localhost:${config.port}/settings/location`, {
    latitude: latitude,
    magDeclination: magDeclination,
    x_offset: x_offset,
    y_offset: y_offset,
    z_offset: z_offset
  })
  .then(r => r.data);
}

async function getFlags() {
  return axios.get(`http://localhost:${config.port}/flags`)
    .then(r => r.data);
}

export { getAllSettings, getAPSettings, getFlags, getLocationSettings, setAPSettings, setLocationSettings };
