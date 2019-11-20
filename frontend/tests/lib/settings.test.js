import MockAdapter from 'axios-mock-adapter';
import { getAllSettings, getFlags } from '../../src/lib/settings';
import Axios from 'axios';

import config from '../../src/config';

const mock = new MockAdapter(Axios);

afterEach(() => {
  mock.reset();
})

describe('getAllSettings', () => {
  beforeEach(() => {
    mock.onGet(`http://localhost:${config.port}/settings?q=debug`).reply(200, {
      apSettings: {
        ssid: "foo",
        key: "bar",
      }
    });
  })

  it('returns expected value', async () => {
    const res = await getAllSettings();
    expect(res).toEqual({
      apSettings: {
        ssid: "foo",
        key: "bar",
      }
    });
  });
});

describe('getFlags', () => {
  beforeEach(() => {
    mock.onGet(`http://localhost:${config.port}/flags`).reply(200, {
      needsAPSettings: false,
      needsLocationSettings: true
    });
  })

  it('returns expected value', async () => {
    const res = await getFlags();
    expect(res).toEqual({ needsAPSettings: false, needsLocationSettings: true });
  });
});
