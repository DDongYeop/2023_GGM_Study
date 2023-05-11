const url = require('url');
const {URL} = url;
const myURL = new URL('https://github.com/DDongYeop/2023_GGM_Study/blob/main/Unity/1ST/BladeBot/ProjectSettings/Packages/com.unity.testtools.codecoverage/Settings.json');
console.log('new URL(): ', myURL);
console.log('url.format(): ', url.format(myURL));
