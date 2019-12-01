import MockAdapter from 'axios-mock-adapter';
import { getAllSettings, getAPSettings, getFlags, getLocationSettings, setAPSettings, setLocationSettings } from '../../src/lib/settings';
import Axios from 'axios';

import config from '../../src/config';

const mock = new MockAdapter(Axios);

afterEach(() => {
  mock.reset();
})

describe('getAllSettings', () => {
  beforeEach(() => {
    mock.onGet(`${config.endpoint}/settings/debug`).reply(200, {
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

describe('getAPSettings', () => {
  beforeEach(() => {
    mock.onGet(`${config.endpoint}/settings/ap`).reply(200, {
      ssid: "foo",
      key: "bar",
    });
  })

  it('returns expected value', async () => {
    const res = await getAPSettings();
    expect(res).toEqual({
      ssid: "foo",
      key: "bar",
    });
  });
});

describe('setAPSettings', () => {
  beforeEach(() => {
    mock.onPost(`${config.endpoint}/settings/ap`).reply(200, {
      ssid: "foo2",
      key: "bar2",
    });
  })

  it('returns posted value', async () => {
    const res = await setAPSettings("foo2", "bar2");
    expect(res).toEqual({
      ssid: "foo2",
      key: "bar2",
    });
  });
});

describe('getLocationSettings', () => {
  beforeEach(() => {
    mock.onGet(`${config.endpoint}/settings/location`).reply(200, {
      "latitude": -37.74,
      "magDeclination": 11.64,
      "x_offset": 0,
      "y_offset": 0,
      "z_offset": 0
    });
  })

  it('returns expected value', async () => {
    const res = await getLocationSettings();
    expect(res).toEqual({
      "latitude": -37.74,
      "magDeclination": 11.64,
      "x_offset": 0,
      "y_offset": 0,
      "z_offset": 0
    });
  });
});

describe('setLocationSettings', () => {
  beforeEach(() => {
    mock.onPost(`${config.endpoint}/settings/location`, {
      "latitude": -37.74,
      "magDeclination": 11.64,
      "x_offset": 1,
      "y_offset": 2,
      "z_offset": 3
    }).reply(200, {
      "latitude": -37.74,
      "magDeclination": 11.64,
      "x_offset": 1,
      "y_offset": 2,
      "z_offset": 3
    });
  })

  it('returns expected value', async () => {
    const res = await setLocationSettings(-37.74, 11.64, 1, 2, 3);
    expect(res).toEqual({
      "latitude": -37.74,
      "magDeclination": 11.64,
      "x_offset": 1,
      "y_offset": 2,
      "z_offset": 3
    });
  });
});



describe('getFlags', () => {
  beforeEach(() => {
    mock.onGet(`${config.endpoint}/flags`).reply(200, {
      needsAPSettings: false,
      needsLocationSettings: true
    });
  })

  it('returns expected value', async () => {
    const res = await getFlags();
    expect(res).toEqual({ needsAPSettings: false, needsLocationSettings: true });
  });
});
