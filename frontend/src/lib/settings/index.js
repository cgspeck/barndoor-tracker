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

async function getFlags() {
  return axios.get(`http://localhost:${config.port}/flags`)
    .then(r => r.data);
}

export { getAllSettings, getAPSettings, getFlags };
