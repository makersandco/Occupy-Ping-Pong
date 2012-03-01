require './opp_server.rb'

use Rack::ShowExceptions

run OppServer.new