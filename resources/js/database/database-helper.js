(function () {
  function databaseHelper(pathFile) {
    const knex = require('knex')({
      client: 'sqlite3',
      connection: {
        filename: pathFile,
      },
      useNullAsDefault: true,
    });

    this.insertEvent = function(datetimeEvent, isLeapYear) {
      knex('events').insert({lunar_date: datetimeEvent, leap_year: isLeapYear})
      .catch(e => {
        console.error(e)
      })
    }

    this.selectEvent = function(id) {
      return knex('events').select('*')
    }

    knex.schema.hasTable('events').then(function(exists) {
      /*init tables here*/
      if (!exists) {
        knex.schema.createTable('events', table => {
          table.increments('id').primary();
          table.datetime('lunar_date');
          table.boolean('leap_year');
        })
        .catch(e => {
          console.error(e);
        });
      }
    })
    .catch(e => {
      console.error(e);
    });

  }

  module.exports.databaseHelper = databaseHelper
}())

