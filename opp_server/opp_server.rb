require 'sinatra'
require 'json'

class OppServer < Sinatra::Application
  @@occupied=0
  get '/' do
    "<h1>Occupy Ping Pong!</h1><br/><h2>{\"occupied\": #{@@occupied}}</h2>"
  end
  get '/status.json' do
    "{\"occupied\": #{@@occupied}}"
  end
  put '/status.json' do
    request.body.rewind  # in case someone already read it
    data = JSON.parse request.body.read
    @@occupied = data['occupied']
    "{\"occupied\": #{@@occupied}}"
  end
end