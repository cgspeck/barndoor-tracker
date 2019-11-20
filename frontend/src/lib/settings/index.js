import axios from 'axios';
import config from '../../config';

async function getAllSettings() {
  return axios.get(`http://localhost:${config.port}/settings?q=debug`)
    .then(r => r.data);
}

async function getFlags() {
  return axios.get(`http://localhost:${config.port}/flags`)
    .then(r => r.data);
}

export { getAllSettings, getFlags };
