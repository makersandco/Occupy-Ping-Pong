require 'sinatra'

class OppServer < Sinatra::Application
  get '/' do
    '<h1>Occupy Ping Pong!</h1>'
  end
end