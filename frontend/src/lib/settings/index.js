import config from '../../config';

async function getAllSettings() {
  const response = await fetch(`http://localhost:${config.port}/settings?q=debug`);
  return await response.json();
}

export { getAllSettings };
