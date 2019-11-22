import MockAdapter from 'axios-mock-adapter';
import { getAllSettings, getAPSettings, getFlags, setAPSettings } from '../../src/lib/settings';
import Axios from 'axios';

import config from '../../src/config';

const mock = new MockAdapter(Axios);

afterEach(() => {
  mock.reset();
})

describe('getAllSettings', () => {
  beforeEach(() => {
    mock.onGet(`http://localhost:${config.port}/settings/debug`).reply(200, {
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
    mock.onGet(`http://localhost:${config.port}/settings/ap`).reply(200, {
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
    mock.onPost(`http://localhost:${config.port}/settings/ap`).reply(200, {
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
