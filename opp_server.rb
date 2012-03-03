require 'sinatra'
require 'json'

class OppServer < Sinatra::Application
  @@occupied=0
  get '/' do
    haml :index, :locals => {:occupied => @@occupied, :indicator_class => indicator(@@occupied)}
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
  def indicator(state)
    if(state == 0)
      :vacant
    else
      :occupied
    end
        
  end
end