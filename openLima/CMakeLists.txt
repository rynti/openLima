# Copyright (C) 2011 Robert Boehm
# This file is part of openLima.
#
# You should have received a copy of the GNU Lesser General Public License
# along with openLima. If not, see: <http://www.gnu.org/licenses/>.
#
# openLima & LimaBeans

cmake_minimum_required(VERSION 2.6)
project(openLima)

set(Boost_USE_STATIC_LIBS ON)
add_definitions(-D_UNICODE -DUNICODE)

add_subdirectory(openLima)
add_subdirectory(LimaBeans)